#include "dummy/server/map_observer.hpp"
#include "dummy/server/map.hpp"

namespace Dummy {
namespace Server {

MapObserver::MapObserver() {}
MapObserver::MapObserver(std::uint32_t id) : m_id(id) {}
MapObserver::MapObserver(std::uint32_t id, std::weak_ptr<Map> map)
    : m_id(id), m_map(map) {}

void MapObserver::setMap(std::weak_ptr<Map> map) {
    m_map = map;
}

/*
void MapObserver::leaveCurrentMap() {
    auto self(shared_from_this());
    if (auto m = m_map.lock()) {
        m->removeObserver(m_id);
        m_map.reset();
    }
}
*/

void MapObserver::setID(std::uint32_t id) {
    m_id = id;
}

void MapObserver::resetID() {
    m_id.reset();
}

} // namespace Server
} // namespace Dummy
