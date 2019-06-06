#pragma once

#include <map>
#include <memory>
#include <string>

namespace Dummy {

namespace Core {
class Map;
} // namespace Core

namespace Server {

class AbstractGameServer;
class Instance;
class Player;

class Map {
public:
    using PlayersList = std::map<std::string, std::shared_ptr<Player>>;
    Map(Instance&, const ::Dummy::Core::Map&);
    void addPlayer(std::shared_ptr<Player>);
    void removePlayer(std::shared_ptr<Player>);
    bool isBlocking(std::uint16_t, std::uint16_t) const;
    const PlayersList& players() const {
        return m_players;
    }
private:
    Instance& m_instance;
    const Dummy::Core::Map& m_map;
    PlayersList m_players;

};

} // namespace Server
} // namespace Dummy
