#include <dummy/core/map.hpp>

#include <dummy/server/abstract_game_server.hpp>
#include <dummy/server/foe.hpp>
#include <dummy/server/player.hpp>
#include <dummy/server/map.hpp>
#include <dummy/server/map_observer.hpp>

namespace Dummy {
namespace Server {

Map::Map(
    Instance& instance,
    const ::Dummy::Remote::Map& map,
    boost::asio::io_context& ioContext
) : m_instance(instance),
    m_map(map),
    m_ioContext(ioContext),
    m_idGenerator(0)
{
    std::size_t index(0);

    for (const auto& foe: m_map.foes()) {
        /*
        std::stringstream ss;
        ss << "NPC " << index++;
        //m_foes[ss.str()] = Foe(foe, ss.str());
        */
        addObserver(std::make_shared<Foe>(foe));
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

void Map::addObserver(std::shared_ptr<MapObserver> mapObserver) {
    // XXX: Should not be problematic. For now.
    while(m_observers.find(++m_idGenerator) != std::end(m_observers));

    mapObserver->setID(++m_idGenerator);
    m_observers[m_idGenerator] = mapObserver;
}

void Map::removeObserver(std::uint32_t id) {
    if (m_observers.find(id) != std::end(m_observers)) {
        auto observer = m_observers[id].lock();
        if (nullptr != observer) {
            observer->resetID();
        }
        m_observers.erase(id);
    }
}

bool
Map::isBlocking(std::uint16_t x, std::uint16_t y, std::uint8_t floor) const {
    // XXX: refactor this.
    //return m_map.isBlocking(x, y);
    return false;
}

void Map::dispatchMessage(std::uint32_t author, const std::string& message) {
    for (auto& [name, player]: m_players) {
        player->gameSession().receiveMessage(author, message);
    }
}

} // namespace Server
} // namespace Dummy
