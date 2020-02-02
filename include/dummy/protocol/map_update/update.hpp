#pragma once

#include <cstdint>

namespace Dummy {

namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

namespace MapUpdate {
class MapUpdateVisitor;
class Update
{
public:
    Update();
    virtual void accept(MapUpdateVisitor&) const                     = 0;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const = 0;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&)          = 0;
};

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
