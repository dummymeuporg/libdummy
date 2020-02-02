#include "dummy/protocol/map_update/living_on.hpp"

#include "dummy/protocol/map_update/map_update_visitor.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

LivingOn::LivingOn(uint32_t id, tilecoords xy, uint8_t floor,
                   const std::string& chipset,
                   Dummy::Core::Character::Direction direction)
    : CharacterPosition(id, xy, direction)
    , m_chipset(chipset)
    , m_floor(floor)
{}

void LivingOn::accept(MapUpdateVisitor& visitor) const
{
    visitor.visitMapUpdate(*this);
}

void LivingOn::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const
{
    packet << m_id << m_xy.first << m_xy.second << m_floor << m_chipset
           << static_cast<uint8_t>(m_direction);
}

void LivingOn::readFrom(Dummy::Protocol::IncomingPacket& packet)
{
    packet >> m_id >> m_xy.first >> m_xy.second >> m_floor >> m_chipset
        >> reinterpret_cast<uint8_t&>(m_direction);
}

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
