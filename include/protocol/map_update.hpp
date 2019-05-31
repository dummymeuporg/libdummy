#pragma once

#include <cstdint>

namespace Dummy {

namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

class MapUpdate {
public:
    MapUpdate();

    friend const OutgoingPacket&
    operator<<(OutgoingPacket& op, const MapUpdate& mapUpdate) {
        mapUpdate._streamToPacket(op);
        return op;
    }

    friend IncomingPacket&
    operator>>(IncomingPacket& ip, MapUpdate& mapUpdate) {
        mapUpdate._streamFromPacket(ip);
        return ip;
    }

    virtual std::uint16_t code() = 0;

protected:
    virtual void _streamToPacket(OutgoingPacket&) const = 0;
    virtual void _streamFromPacket(IncomingPacket&) = 0;
};

} // namespace Protocol

} // namespace Dummy
