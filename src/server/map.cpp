#include <dummy/core/map.hpp>

#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/foe.hpp>
#include <dummy/server/player.hpp>
#include <dummy/server/map.hpp>

namespace Dummy {
namespace Server {

Map::Map(
    Instance& instance,
    const ::Dummy::Remote::Map& map,
    boost::asio::io_context& ioContext
) : m_instance(instance), m_map(map), m_ioContext(ioContext)
{
    std::size_t index(0);

    for (const auto& foe: m_map.foes()) {
        std::stringstream ss;
        ss << "NPC " << index++;
        m_foes[ss.str()] = Foe(foe, ss.str());
    }
}

void
Map::addPlayer(std::shared_ptr<Player> player) {
    if (m_players.find(player->name()) == std::end(m_players)) {
        m_players[player->name()] = player;
        player->setMap(shared_from_this());
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

void Map::dispatchMessage(
    const std::string& author,
    const std::string& message
) {
    for (auto& [name, player]: m_players) {
        player->gameSession().receiveMessage(author, message);
    }
}

} // namespace Server
} // namespace Dummy
