#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "protocol/map_update/map_update_visitor.hpp"
#include "protocol/map_update/character_position.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

CharacterPosition::CharacterPosition(
    std::uint16_t x,
    std::uint16_t y,
    const std::string& name,
    Dummy::Core::Character::Direction direction
) : m_x(x), m_y(y), m_name(name), m_direction(direction)
{
}

void CharacterPosition::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

void
CharacterPosition::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {
    packet << m_name << m_x << m_y;
}

void CharacterPosition::readFrom(Dummy::Protocol::IncomingPacket& packet) {
    packet >> m_name >> m_x >> m_y;
}

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
