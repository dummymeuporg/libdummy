#pragma once

#include <memory>

#include <boost/asio.hpp>

#include "dummy/server/abstract_game_server.hpp"
#include "dummy/server/map.hpp"

namespace Dummy {
namespace Server {

class Instance : public std::enable_shared_from_this<Instance> {
public:
    Instance(AbstractGameServer&,
             boost::asio::io_context&,
             const std::string&);

    const std::string& name() const {
        return m_name;
    }

    void addPlayer(const std::string&, std::weak_ptr<Player>);
    void removePlayer(const std::string&);

    std::size_t countPlayers() const {
        return m_players.size();
    }

    std::weak_ptr<Map> map(const std::string&);

private:
    AbstractGameServer& m_abstractGameServer;
    boost::asio::io_context& m_ioContext;
    std::string m_name;
    std::map<std::string,
             std::shared_ptr<Map>> m_maps;
    std::map<std::string, std::weak_ptr<Player>> m_players;
};

} // namespace Server
} // namespace Dummy
