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
    using Observers = std::map<std::uint32_t, std::weak_ptr<MapObserver>>;
    Map(Instance&, const Remote::Map&, boost::asio::io_context&);
    void addObserver(std::shared_ptr<MapObserver>);
    void removeObserver(std::uint32_t);
    void addPlayer(std::shared_ptr<Player>);
    void removePlayer(std::shared_ptr<Player>);
    void dispatchMessage(
        const std::uint32_t author,
        const std::string& message
    );
    bool isBlocking(std::uint16_t, std::uint16_t, std::uint8_t) const;
    const PlayersList& players() const {
        return m_players;
    }
    const FoesList& foes() const {
        return m_foes;
    }

    const Observers& observers() const {
        return m_observers;
    }
private:
    Instance& m_instance;
    const Dummy::Remote::Map& m_map;
    boost::asio::io_context& m_ioContext;
    PlayersList m_players;
    FoesList m_foes;
    Observers m_observers;
    std::uint32_t m_idGenerator;

};

} // namespace Server
} // namespace Dummy
