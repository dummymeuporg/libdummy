#include <dummy/core/map.hpp>

#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/player.hpp>
#include <dummy/server/map.hpp>

namespace Dummy {
namespace Server {

Map::Map(Instance& instance, const ::Dummy::Remote::Map& map)
    : m_instance(instance), m_map(map)
{
}

void
Map::addPlayer(std::shared_ptr<Player> player) {
    if (m_players.find(player->name()) == std::end(m_players)) {
        m_players[player->name()] = player;
    }
}

void
Map::removePlayer(std::shared_ptr<Player> player) {
    if (m_players.find(player->name()) != std::end(m_players)) {
        std::cerr << "Bye bye " << player->name() << std::endl;
        m_players.erase(player->name());
    }
}

bool
Map::isBlocking(std::uint16_t x, std::uint16_t y, std::uint8_t floor) const {
    // XXX: refactor this.
    //return m_map.isBlocking(x, y);
    return false;
}

} // namespace Server
} // namespace Dummy
