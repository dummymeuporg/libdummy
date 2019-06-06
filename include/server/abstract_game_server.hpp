#pragma once

#include <filesystem>
#include <map>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "core/account.hpp"
#include "core/character.hpp"
#include "core/project.hpp"

#include "server/instance.hpp"

namespace fs = std::filesystem;
using boost::asio::ip::tcp;

namespace Dummy {
namespace Server {

class Player;
class ServerMap;

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

    void connect(const boost::uuids::uuid& sessionID,
                 const std::string&);
    void disconnect(const std::string&);
    bool isPending(const boost::uuids::uuid&) const;
    bool isAuthenticated(const std::string&) const;

    /* Character creation. */
    bool characterExists(const Core::Character&) const;
    bool skinExists(const std::string&) const;

    ::Dummy::Core::Character createCharacter(const ::Dummy::Core::Account&,
                                           const std::string& characterName,
                                           const std::string& skin) const;

    void createCharacterFile(
        const ::Dummy::Core::Account&,
        const ::Dummy::Core::Character&
    ) const;

    void saveCharacter(
        const ::Dummy::Core::Account&,
        const ::Dummy::Core::Character&
    ) const;

    virtual void run() = 0;

protected:
    void _spawnMainInstance();

    ::Dummy::Core::Project m_project;
    fs::path m_serverPath;
    Instance m_mainInstance;
    std::map<boost::uuids::uuid,
             std::shared_ptr<::Dummy::Core::Account>> m_pendingAccounts;
    std::map<std::string,
             std::shared_ptr<::Dummy::Core::Account>> m_connectedAccounts;
};

} // namespace Server
} // namespace Dummy
