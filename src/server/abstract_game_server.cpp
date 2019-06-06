#include <iostream>


#include "server/abstract_game_server.hpp"
#include "server/errors.hpp"
#include "server/game_session.hpp"

namespace Dummy {
namespace Server {

AbstractGameServer::AbstractGameServer(
    const fs::path& projectPath,
    const fs::path& serverPath
) : m_project(projectPath),
    m_serverPath(serverPath),
    m_mainInstance(*this)
{
    m_project.load();
    _spawnMainInstance();
}

void AbstractGameServer::_spawnMainInstance()
{
    m_mainInstance.spawnMaps();
}

void AbstractGameServer::connect(
    const boost::uuids::uuid& sessionID,
    const std::string& accountName)
{
    if (m_pendingAccounts.find(sessionID) == m_pendingAccounts.end()) {
        return; // Throw an exception?
    }

    if (m_connectedAccounts.find(accountName) == m_connectedAccounts.end()) {
        return; // Throw an exception?
    }

    std::cerr << "Connect account " << accountName << std::endl;
    std::shared_ptr<Dummy::Core::Account> account =
        m_pendingAccounts[sessionID];
    m_connectedAccounts[accountName] = account;
}

bool
AbstractGameServer::isAuthenticated(const std::string& accountName) const {
    return m_connectedAccounts.find(accountName) != m_connectedAccounts.end();
}

bool
AbstractGameServer::isPending(const boost::uuids::uuid& id) const {
    return m_pendingAccounts.find(id) != m_pendingAccounts.end();
}

bool
AbstractGameServer::skinExists(const std::string& skin) const {
    return fs::exists(m_project.projectPath() / "chipsets" / skin);
}

bool
AbstractGameServer::characterExists(
    const Dummy::Core::Character& character
) const {
    // get canonical name, check if file exists.
    // that’s it.
    return fs::exists(m_serverPath / "characters" / character.filename());
}

void AbstractGameServer::createCharacterFile(
    const Dummy::Core::Account& account,
    const Dummy::Core::Character& character
) const
{
    saveCharacter(account, character);
    fs::path symlinkPath(m_serverPath / "characters" / character.filename());

    // Create a (relative) symlink to reference the character.
    fs::create_symlink(
        fs::path("..")
        / "accounts"
        / account.name()
        / "characters"
        / character.filename(),
        symlinkPath
    );

}

void AbstractGameServer::saveCharacter(
    const Dummy::Core::Account& account,
    const Dummy::Core::Character& character
) const
{
    fs::path characterFullPath(m_serverPath
        / "accounts"
        / account.name()
        / "characters"
        / character.filename()
    );

    std::cerr << "Path:" << characterFullPath.string() << std::endl;
    std::ofstream ofs(characterFullPath.string(),
                      std::ofstream::out | std::ios::binary);
    ofs << character;
    ofs.close();
}

Dummy::Core::Character
AbstractGameServer::createCharacter(const Dummy::Core::Account& account,
                                    const std::string& characterName,
                                    const std::string& skin) const
{
    Dummy::Core::Character chr;

    chr.setName(characterName);

    if(characterExists(chr)) {
        throw CharacterAlreadyExists();
    }

    chr.setSkin(skin);

    if (!skinExists(chr.skin())) {
        throw SkinDoesNotExist();
    }

    // From now, we consider the character being valid.
    std::pair<std::uint16_t, std::uint16_t>
        position(m_project.startingPosition());
    position.first *= 2;
    position.second *= 2;
    chr.setPosition(position);
    chr.setMapLocation(m_project.startingMap());

    createCharacterFile(account, chr);

    return chr;

}

} // namespace Server
} // namespace Dummy
