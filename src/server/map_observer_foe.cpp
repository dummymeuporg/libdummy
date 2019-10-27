#include <dummy/server/map_observer_foe.hpp>

namespace Dummy {
namespace Server {

MapObserverFoe::MapObserverFoe(
    std::uint32_t id,
    std::weak_ptr<Foe> foe
) : MapObserver(id), m_foe(foe)
{}

} // namespace Server
} // namespace Dummy
