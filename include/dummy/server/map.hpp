#pragma once

#include <map>
#include <memory>
#include <string>

#include <boost/asio.hpp>

#include <dummy/server/foe.hpp>

namespace Dummy {

namespace Core {
class Foe;
} // namespace Core

namespace Remote {
class Map;
} // namespace Core

namespace Server {

class AbstractGameServer;
class Instance;
class MapObserver;
class Player;

class Map : public std::enable_shared_from_this<Map> {
public:
    using PlayersList = std::map<std::string, std::shared_ptr<Player>>;
    using FoesList = std::map<std::string, Dummy::Server::Foe>;
    Map(Instance&, const Remote::Map&, boost::asio::io_context&);
    void addPlayer(std::shared_ptr<Player>);
    void removePlayer(std::shared_ptr<Player>);
    void dispatchMessage(
        const std::string& author,
        const std::string& message
    );
    bool isBlocking(std::uint16_t, std::uint16_t, std::uint8_t) const;
    const PlayersList& players() const {
        return m_players;
    }
    const FoesList& foes() const {
        return m_foes;
    }
private:
    Instance& m_instance;
    const Dummy::Remote::Map& m_map;
    boost::asio::io_context& m_ioContext;
    PlayersList m_players;
    FoesList m_foes;
    std::map<std::string, std::shared_ptr<MapObserver>> m_mapObservers;

};

} // namespace Server
} // namespace Dummy
