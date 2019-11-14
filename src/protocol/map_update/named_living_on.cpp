#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/protocol/map_update/map_update_visitor.hpp>
#include <dummy/protocol/map_update/named_living_on.hpp>

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

NamedLivingOn::NamedLivingOn(std::uint32_t id,
                             std::uint16_t x,
                             std::uint16_t y,
                             std::uint8_t floor,
                             std::uint8_t velocity,
                             const std::string& name,
                             const std::string& chipset,
                             Dummy::Core::Character::Direction direction)
    : CharacterPosition(id, x, y, direction),
      m_name(name),
      m_chipset(chipset),
      m_floor(floor),
      m_velocity(velocity)
{
}

void NamedLivingOn::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

void
NamedLivingOn::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {
    packet << m_id << m_name << m_chipset << m_x << m_y << m_floor <<
        m_velocity << static_cast<std::uint8_t>(m_direction);
}

void NamedLivingOn::readFrom(Dummy::Protocol::IncomingPacket& packet) {
    packet >> m_id >> m_name >> m_chipset >> m_x >> m_y >> m_floor >>
        m_velocity >> reinterpret_cast<std::uint8_t&>(m_direction);
}


} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
