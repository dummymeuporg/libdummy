#include <iostream>
#include <filesystem>

#include <dummy/remote/map.hpp>
#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/account.hpp>
#include <dummy/server/errors.hpp>
#include <dummy/server/game_session.hpp>
#include <dummy/server/game_session_communicator.hpp>

namespace fs = std::filesystem;

namespace Dummy {
namespace Server {

AbstractGameServer::AbstractGameServer(
   boost::asio::io_context& ioContext,
   const fs::path& projectPath,
   const fs::path& serverPath
) : m_ioContext(ioContext),
    m_project(projectPath),
    m_serverPath(serverPath),
    m_mainInstance(*this, m_ioContext)
{
    m_project.load();
    _spawnMainInstance();
}

void AbstractGameServer::_spawnMainInstance()
{
    m_mainInstance.spawnMaps();
}

void AbstractGameServer::run() {

}

void AbstractGameServer::addPending(
    const std::string& sessionID,
    const std::string& accountName
) {
    m_pendingAccounts[sessionID] = std::make_shared<Account>(
        accountName, sessionID
    );
}

std::shared_ptr<Account> AbstractGameServer::connect(
    const std::string& sessionID,
    const std::string& accountName
)
{
    if (m_pendingAccounts.find(sessionID) == m_pendingAccounts.end()) {
        throw AccountNotPending();
    }

    if (m_connectedAccounts.find(accountName) != m_connectedAccounts.end()) {
        // XXX: disconnect the account.
        //throw AlreadyConnected();
    }

    std::cerr << "Connect account " << accountName << std::endl;
    std::shared_ptr<Account> account =
        m_pendingAccounts[sessionID];
    m_connectedAccounts[accountName] = account;
    return account;
}

bool
AbstractGameServer::isAuthenticated(const std::string& accountName) const {
    return m_connectedAccounts.find(accountName) != m_connectedAccounts.end();
}

bool
AbstractGameServer::isPending(const std::string& id) const {
    return m_pendingAccounts.find(id) != m_pendingAccounts.end();
}

bool
AbstractGameServer::skinExists(const std::string& skin) const {
    return fs::exists(m_project.projectPath() / "chipsets" / skin);
}

bool
AbstractGameServer::characterExists(const Dummy::Core::Character& character)
const {
    // get canonical name, check if file exists.
    // that’s it.
    return fs::exists(m_serverPath / "characters" / character.filename());
}

void AbstractGameServer::createCharacterFile(
    const Account& account,
    const Dummy::Core::Character& character
) const
{
    saveCharacter(account, character);
    fs::path symlinkPath(m_serverPath / "characters" / character.filename());

    // Create a (relative) symlink to reference the character.
    createSymLink(
        (fs::path("..")
        / "accounts"
        / account.name()
        / "characters"
        / character.filename()).string(),
        symlinkPath.string()
    );

}

void AbstractGameServer::createSymLink(
    const std::string& src,
    const std::string& dst
) const {
#if defined(WIN32) // Windows
    //XXX: Create some real file, with content indicating the relative
    //path to the file being 'symlinked'
    std::ofstream ofs(dst);
    if (ofs.is_open()) {
        ofs.write(src.c_str(), src.size());
        ofs.close();
    }
#else // Not Windows
    // Create a (relative) symlink to reference the character.
    fs::create_symlink(src, dst);
#endif
}

void AbstractGameServer::saveCharacter(
    const Account& account,
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
AbstractGameServer::createCharacter(const Account& account,
                                    const std::string& characterName,
                                    const std::string& skin) const
{
    Dummy::Core::Character chr;

    if (characterName.empty()) {
        throw CharacterNameEmpty();
    }

    chr.setName(characterName);

    if(characterExists(chr)) {
        throw NameAlreadyTaken();
    }

    chr.setSkin(skin);

    if (!skinExists(chr.skin())) {
        throw InvalidSkin();
    }

    // From now, we consider the character being valid.
    const Dummy::Core::StartingPoint& startingPoint(m_project.startingPoint());
    std::pair<std::uint16_t, std::uint16_t>
        position(startingPoint.position());
    position.first *= 2;
    position.second *= 2;
    chr.setPosition(position);
    chr.setMapLocation(startingPoint.mapName());
    chr.setFloor(startingPoint.floor());
    chr.setInstance(startingPoint.instance());

    createCharacterFile(account, chr);

    return chr;

}

std::shared_ptr<GameSession>
AbstractGameServer::buildGameSession(
    std::shared_ptr<GameSessionCommunicator> communicator
)
{
    auto gameSession(
        std::make_shared<GameSession>(*this, communicator, m_ioContext)
    );
    // XXX: We keep track of the game session, otherwise it ain't got
    // referenced, thus destroyed.
    m_gameSessions.emplace(gameSession);
    return gameSession;
}

void
AbstractGameServer::removeSession(std::shared_ptr<GameSession> gameSession) {
    std::cerr << "Removing game session." << std::endl;
    m_gameSessions.erase(gameSession);
}

} // namespace Server
} // namespace Dummy
