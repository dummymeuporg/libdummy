#pragma once

#include <filesystem>
#include <map>
#include <memory>

#include <boost/asio.hpp>

#include <dummy/core/character.hpp>
#include <dummy/core/project.hpp>

#include <dummy/server/instance.hpp>
#include <dummy/server/project.hpp>

namespace fs = std::filesystem;

namespace Dummy {
namespace Server {

class Account;
class GameSession;
class GameSessionCommunicator;
class Player;
class Map;

class AbstractGameServer {
public:
    AbstractGameServer(boost::asio::io_context& ioContext,
                       const fs::path& projectPath,
                       const fs::path& serverPath);

    const fs::path& serverPath() const {
        return m_serverPath;
    }

    const Project& project() const {
        return m_project;
    }

    std::shared_ptr<Account>
    connect(const std::string&, const std::string&);
    void disconnect(const std::string&);
    void addPending(const std::string&, const std::string&);
    bool isPending(const std::string&) const;
    bool isAuthenticated(const std::string&) const;
    Instance& mainInstance() {
        return m_mainInstance;
    }

    /* Character creation. */
    bool characterExists(const Core::Character&) const;
    bool skinExists(const std::string&) const;

    std::shared_ptr<GameSession> buildGameSession(
        std::shared_ptr<Dummy::Server::GameSessionCommunicator>
    );

    ::Dummy::Core::Character createCharacter(const Account&,
                                             const std::string& characterName,
                                             const std::string& skin) const;

    void
    createCharacterFile(const Account&, const ::Dummy::Core::Character&) const;

    void
    saveCharacter(const Account&, const ::Dummy::Core::Character&) const;

    virtual void run();

protected:
    void _spawnMainInstance();

    boost::asio::io_service& m_ioContext;
    Project m_project;
    fs::path m_serverPath;
    Instance m_mainInstance;
    std::map<std::string,
             std::shared_ptr<Account>> m_pendingAccounts;
    std::map<std::string,
             std::shared_ptr<Account>> m_connectedAccounts;
};

} // namespace Server
} // namespace Dummy
