#pragma once

namespace Dummy {
namespace Protocol {
namespace MapUpdate {
class Update;
} // namespace MapUpdate
} // namespace Protocol

namespace Server {

class Map;

class MapObserver {
public:
    virtual void notify(const Map&, const Protocol::MapUpdate::Update&) = 0;
};

} // namespace Server
} // namespace Dummy
