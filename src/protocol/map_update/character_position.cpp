#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/protocol/map_update/map_update_visitor.hpp>
#include <dummy/protocol/map_update/character_position.hpp>

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

CharacterPosition::CharacterPosition(
    std::uint32_t id,
    std::uint16_t x,
    std::uint16_t y,
    Dummy::Core::Character::Direction direction
) : m_id(id), m_x(x), m_y(y), m_direction(direction)
{
}

void CharacterPosition::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

void
CharacterPosition::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {
    packet << m_id << m_x << m_y << static_cast<std::uint8_t>(m_direction);
}

void CharacterPosition::readFrom(Dummy::Protocol::IncomingPacket& packet) {
    std::uint8_t direction;
    packet >> m_id >> m_x >> m_y >> direction;
    m_direction = static_cast<Dummy::Core::Character::Direction>(direction);
}

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
