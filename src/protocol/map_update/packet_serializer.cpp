#include "dummy/protocol/map_update/packet_serializer.hpp"

#include "dummy/protocol/bridge.hpp"
#include "dummy/protocol/map_update/character_floor.hpp"
#include "dummy/protocol/map_update/living_off.hpp"
#include "dummy/protocol/map_update/living_on.hpp"
#include "dummy/protocol/map_update/named_living_on.hpp"
#include "dummy/protocol/map_update/update.hpp"
#include "dummy/protocol/outgoing_packet.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

PacketSerializer::PacketSerializer(OutgoingPacket& packet)
    : m_packet(packet)
{}

void PacketSerializer::visit(const Update& update)
{
    update.accept(*this);
}

void PacketSerializer::visitMapUpdate(const LivingOff& update)
{
    m_packet << Bridge::LIVING_OFF << update.id();
}

void PacketSerializer::visitMapUpdate(const LivingOn& update)
{
    m_packet << Bridge::LIVING_ON << update.id() << update.x() << update.y()
             << update.floor() << update.chipset()
             << static_cast<std::uint8_t>(update.direction());
}

void PacketSerializer::visitMapUpdate(const NamedLivingOn& update)
{
    m_packet << Bridge::NAMED_LIVING_ON << update.id() << update.x()
             << update.y() << update.floor() << update.name()
             << update.chipset()
             << static_cast<std::uint8_t>(update.direction());
}

void PacketSerializer::visitMapUpdate(const CharacterPosition& update)
{
    m_packet << Bridge::CHARACTER_POSITION << update.id() << update.x()
             << update.y() << static_cast<std::uint8_t>(update.direction());
}

void PacketSerializer::visitMapUpdate(const CharacterFloor& update)
{
    m_packet << Bridge::CHARACTER_FLOOR << update.name() << update.floor();
}

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
