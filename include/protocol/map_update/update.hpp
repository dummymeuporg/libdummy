#pragma once

#include <cstdint>

namespace Dummy {

namespace Protocol {

namespace MapUpdate {
class MapUpdateVisitor;
class Update {
public:
    Update();
    virtual void accept(MapUpdateVisitor&) const = 0;
};

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
