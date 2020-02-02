#include "dummy/protocol/map_update/character_position.hpp"

#include "dummy/protocol/map_update/map_update_visitor.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

CharacterPosition::CharacterPosition(
    uint32_t id, tilecoords xy, Dummy::Core::Character::Direction direction)
    : m_id(id)
    , m_xy(xy)
    , m_direction(direction)
{}

void CharacterPosition::accept(MapUpdateVisitor& visitor) const
{
    visitor.visitMapUpdate(*this);
}

void CharacterPosition::serializeTo(
    Dummy::Protocol::OutgoingPacket& packet) const
{
    packet << m_id << m_xy.first << m_xy.second
           << static_cast<uint8_t>(m_direction);
}

void CharacterPosition::readFrom(Dummy::Protocol::IncomingPacket& packet)
{
    uint8_t direction;
    packet >> m_id >> m_xy.first >> m_xy.second >> direction;
    m_direction = static_cast<Dummy::Core::Character::Direction>(direction);
}

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
