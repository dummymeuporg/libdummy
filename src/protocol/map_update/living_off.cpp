#include "dummy/protocol/map_update/living_off.hpp"
#include "dummy/protocol/incoming_packet.hpp"
#include "dummy/protocol/map_update/map_update_visitor.hpp"
#include "dummy/protocol/outgoing_packet.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {

LivingOff::LivingOff(const std::uint32_t id)
    : m_id(id)
{}

void LivingOff::accept(MapUpdateVisitor& visitor) const
{
    visitor.visitMapUpdate(*this);
}

void LivingOff::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const
{
    packet << m_id;
}

void LivingOff::readFrom(Dummy::Protocol::IncomingPacket& packet)
{
    packet >> m_id;
}

} // namespace MapUpdate
} // namespace Protocol
} // namespace Dummy
