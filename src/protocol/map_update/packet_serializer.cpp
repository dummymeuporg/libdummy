#include <dummy/protocol/bridge.hpp>
#include <dummy/protocol/map_update/packet_serializer.hpp>
#include <dummy/protocol/map_update/update.hpp>
#include <dummy/protocol/map_update/character_floor.hpp>
#include <dummy/protocol/map_update/character_on.hpp>
#include <dummy/protocol/map_update/character_off.hpp>
#include <dummy/protocol/map_update/character_position.hpp>
#include <dummy/protocol/outgoing_packet.hpp>

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

PacketSerializer::PacketSerializer(OutgoingPacket& packet) : m_packet(packet)
{
}

void PacketSerializer::visit(const Update& update) {
    update.accept(*this);
}

void PacketSerializer::visitMapUpdate(const CharacterOff& update) {
    m_packet << Bridge::CHARACTER_OFF << update.name();
}

void PacketSerializer::visitMapUpdate(const CharacterOn& update) {
    m_packet << Bridge::CHARACTER_ON
        << update.x() << update.y() << update.floor()
        << update.name() << update.chipset()
        << static_cast<std::uint8_t>(update.direction());
}

void PacketSerializer::visitMapUpdate(const CharacterPosition& update) {
    m_packet << Bridge::CHARACTER_POSITION
        << update.x() << update.y() << update.name()
        << static_cast<std::uint8_t>(update.direction());
}

void PacketSerializer::visitMapUpdate(const CharacterFloor& update) {
    m_packet << Bridge::CHARACTER_FLOOR
        << update.name() << update.floor();
}

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
