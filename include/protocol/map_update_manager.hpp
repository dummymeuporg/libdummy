#pragma once

#include <cstdint>

#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"

namespace Dummy {

namespace Protocol {


/* Map updates */
class MapUpdate;
class CharacterInfo;
class CharacterOff;

class MapUpdateManager {
public:
    enum class Code : std::uint16_t {
        CHARACTER_INFO = 1,
        CHARACTER_OFF = 2
    };

    friend
    OutgoingPacket&
    operator<<(OutgoingPacket& pkt, Code c) {
        pkt << static_cast<std::uint16_t>(c);
        return pkt;
    }

    friend
    IncomingPacket&
    operator>>(IncomingPacket& pkt, Code& c) {
        pkt >> reinterpret_cast<std::uint16_t&>(c);
        return pkt;
    }

    static std::shared_ptr<MapUpdate> readMapUpdate(IncomingPacket&);
    static void writeMapUpdate(OutgoingPacket&, const CharacterInfo&);
    static void writeMapUpdate(OutgoingPacket&, const CharacterOff&);
};

} // namespace Protocol

} // namespace Dummy
