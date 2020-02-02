#include "dummy/server/map.hpp"

#include "dummy/remote/map.hpp"
#include "dummy/server/player.hpp"

namespace Dummy {
namespace Server {

Map::Map(Instance& instance, const ::Dummy::Remote::Map& map,
         boost::asio::io_context& ioContext)
    : m_instance(instance)
    , m_map(map)
    , m_ioContext(ioContext)
    , m_idGenerator(0)
{}

void Map::spawn()
{
    for (const auto& foe : m_map.foes()) {
        auto mapFoe(std::make_shared<Foe::Foe>(foe, m_ioContext));
        m_foes.insert(mapFoe);
        addObserver(mapFoe);
        mapFoe->setMap(weak_from_this());
        mapFoe->start();
    }
}

void Map::addPlayer(std::shared_ptr<Player> player)
{
    if (m_players.find(player->name()) == std::end(m_players)) {
        m_players[player->name()] = player;
        player->setMap(shared_from_this());
    }
}

void Map::removePlayer(std::shared_ptr<Player> player)
{
    if (m_players.find(player->name()) != std::end(m_players)) {
        std::cerr << "Bye bye " << player->name() << std::endl;
        m_players.erase(player->name());
    }
}

void Map::addObserver(std::shared_ptr<MapObserver> mapObserver)
{
    // XXX: Should not be problematic. For now.
    while (m_observers.find(++m_idGenerator) != std::end(m_observers))
        ;

    mapObserver->setID(m_idGenerator);
    m_observers[m_idGenerator] = mapObserver;
}

void Map::removeObserver(uint32_t id)
{
    if (m_observers.find(id) != std::end(m_observers)) {
        auto observer = m_observers[id].lock();
        if (nullptr != observer) {
            observer->resetID();
        }
        m_observers.erase(id);
    }
}

bool Map::isBlocking(uint16_t x, uint16_t y, uint8_t floor) const
{
    // XXX: refactor this.
    return m_map.floors().at(floor).isBlocking({x, y});
}

void Map::dispatchMessage(uint32_t author, const std::string& message)
{
    for (auto& [id, observer] : m_observers) {
        auto observerPt = observer.lock();
        if (nullptr != observerPt) {
            observerPt->receiveMessage(author, message);
        }
    }
}

} // namespace Server
} // namespace Dummy
