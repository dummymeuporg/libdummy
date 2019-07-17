#pragma once

#include <map>
#include <memory>
#include <string>

namespace Dummy {

namespace Remote {
class Map;
} // namespace Core

namespace Server {

class AbstractGameServer;
class Instance;
class MapObserver;
class Player;

class Map {
public:
    using PlayersList = std::map<std::string, std::shared_ptr<Player>>;
    Map(Instance&, const Remote::Map&);
    void addPlayer(std::shared_ptr<Player>);
    void removePlayer(std::shared_ptr<Player>);
    bool isBlocking(std::uint16_t, std::uint16_t, std::uint8_t) const;
    const PlayersList& players() const {
        return m_players;
    }
private:
    Instance& m_instance;
    const Dummy::Remote::Map& m_map;
    PlayersList m_players;
    std::map<std::string, std::shared_ptr<MapObserver>> m_mapObservers;

};

} // namespace Server
} // namespace Dummy
