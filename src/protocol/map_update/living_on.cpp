#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/protocol/map_update/map_update_visitor.hpp>
#include <dummy/protocol/map_update/living_on.hpp>

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

LivingOn::LivingOn(std::uint32_t id,
                   std::uint16_t x,
                   std::uint16_t y,
                   std::uint8_t floor,
                   const std::string& chipset,
                   Dummy::Core::Character::Direction direction)
    : CharacterPosition(id, x, y, direction),
      m_chipset(chipset),
      m_floor(floor)
{
}

void LivingOn::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

void
LivingOn::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {
    packet << m_id << m_x << m_y << m_floor << m_chipset
        << static_cast<std::uint8_t>(m_direction);
}

void LivingOn::readFrom(Dummy::Protocol::IncomingPacket& packet) {
    packet >> m_id >> m_x >> m_y >> m_floor >> m_chipset
        >> reinterpret_cast<std::uint8_t&>(m_direction);
}


} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
