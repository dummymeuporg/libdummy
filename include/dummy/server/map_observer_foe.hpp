#pragma once

#include <dummy/server/foe.hpp>
#include <dummy/server/map_observer.hpp>

namespace Dummy {
namespace Server {

class MapObserverFoe : public MapObserver {
public:
    MapObserverFoe(std::uint32_t id, std::weak_ptr<Foe>);
private:
    std::weak_ptr<Foe> m_foe;
};

} // namespace Server
} // namespace Dummy
