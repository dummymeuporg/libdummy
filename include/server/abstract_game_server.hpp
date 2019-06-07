#pragma once

#include <filesystem>
#include <map>
#include <memory>

#include "core/character.hpp"
#include "core/project.hpp"

#include "server/instance.hpp"

namespace fs = std::filesystem;

namespace Dummy {
namespace Server {

class Account;
class GameSession;
class Player;
class Map;

class AbstractGameServer {
public:
    AbstractGameServer(const fs::path& projectPath,
                       const fs::path& serverPath);

    const fs::path& serverPath() const {
        return m_serverPath;
    }

    const ::Dummy::Core::Project& project() const {
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

    std::shared_ptr<GameSession> buildGameSession();

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

    ::Dummy::Core::Project m_project;
    fs::path m_serverPath;
    Instance m_mainInstance;
    std::map<std::string,
             std::shared_ptr<Account>> m_pendingAccounts;
    std::map<std::string,
             std::shared_ptr<Account>> m_connectedAccounts;
};

} // namespace Server
} // namespace Dummy
