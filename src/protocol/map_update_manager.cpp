#include <memory>

#include "protocol/map_update_manager.hpp"
#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "protocol/character_off.hpp"
#include "protocol/character_off.hpp"
#include "protocol/character_position.hpp"

namespace Dummy {

namespace Protocol {

std::shared_ptr<MapUpdate>
MapUpdateManager::readMapUpdate(IncomingPacket& pkt) {
    std::shared_ptr<MapUpdate> mapUpdate = nullptr;
    Code code;
    pkt >> code;

    switch(code) {
    case Code::CHARACTER_INFO: {
        std::uint16_t x, y;
        std::string name, chipset;
        pkt >> x, y, name, chipset;
        mapUpdate = std::dynamic_pointer_cast<MapUpdate>(
            std::make_shared<CharacterPosition>(x, y, name, chipset)
        );
        break;
    }
    case Code::CHARACTER_OFF: {
        std::string name;
        pkt >> name;
        mapUpdate = std::dynamic_pointer_cast<MapUpdate>(
            std::make_shared<CharacterOff>(name)
        );
        break;
    }
    default:
        /* Raise an error? */
        break;
    }
    return mapUpdate;
}

void
MapUpdateManager::writeMapUpdate(
    OutgoingPacket& pkt,
    const CharacterInfo& update)
{
    pkt << Code::CHARACTER_INFO << reinterpret_cast<const MapUpdate&>(update);
}

void
MapUpdateManager::writeMapUpdate(
    OutgoingPacket& pkt,
    const CharacterOff& update)
{
    pkt << Code::CHARACTER_OFF << reinterpret_cast<const MapUpdate&>(update);
}


} // namespace Protocol

} // namespace Dummy
