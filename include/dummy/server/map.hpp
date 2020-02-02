#pragma once

#include <set>

#include "dummy/server/foe/foe.hpp"

namespace Dummy {
namespace Core {
class Foe;
} // namespace Core

namespace Remote {
class Map;
} // namespace Remote

namespace Server {

class AbstractGameServer;
class Instance;
class MapObserver;
class Player;

class Map : public std::enable_shared_from_this<Map>
{
public:
    using PlayersList = std::map<std::string, std::shared_ptr<Player>>;
    using Foes        = std::set<std::shared_ptr<Dummy::Server::Foe::Foe>>;
    using Observers   = std::map<uint32_t, std::weak_ptr<MapObserver>>;
    Map(Instance&, const Remote::Map&, boost::asio::io_context&);
    void spawn();
    void addObserver(std::shared_ptr<MapObserver>);
    void removeObserver(uint32_t);
    void addPlayer(std::shared_ptr<Player>);
    void removePlayer(std::shared_ptr<Player>);
    void dispatchMessage(const uint32_t author,
                         const std::string& message);
    bool isBlocking(uint16_t, uint16_t, uint8_t) const;
    const PlayersList& players() const { return m_players; }
    const Foes& foes() const { return m_foes; }

    const Observers& observers() const { return m_observers; }

private:
    Instance& m_instance;
    const Dummy::Remote::Map& m_map;
    boost::asio::io_context& m_ioContext;
    PlayersList m_players;
    Foes m_foes;
    Observers m_observers;
    uint32_t m_idGenerator;
};

} // namespace Server
} // namespace Dummy
