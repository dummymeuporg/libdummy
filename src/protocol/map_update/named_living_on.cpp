#include "dummy/protocol/map_update/named_living_on.hpp"

#include "dummy/protocol/map_update/map_update_visitor.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

NamedLivingOn::NamedLivingOn(uint32_t id, tilecoords xy, uint8_t floor,
                             const std::string& name,
                             const std::string& chipset,
                             Dummy::Core::Character::Direction direction)
    : CharacterPosition(id, xy, direction)
    , m_name(name)
    , m_chipset(chipset)
    , m_floor(floor)
{}

void NamedLivingOn::accept(MapUpdateVisitor& visitor) const
{
    visitor.visitMapUpdate(*this);
}

void NamedLivingOn::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const
{
    packet << m_id << m_name << m_chipset << m_xy.first << m_xy.second
           << m_floor << static_cast<uint8_t>(m_direction);
}

void NamedLivingOn::readFrom(Dummy::Protocol::IncomingPacket& packet)
{
    packet >> m_id >> m_name >> m_chipset >> m_xy.first >> m_xy.second
        >> m_floor >> reinterpret_cast<uint8_t&>(m_direction);
}


} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
