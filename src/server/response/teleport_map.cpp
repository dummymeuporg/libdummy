#include "dummy/server/response/teleport_map.hpp"
#include "dummy/protocol/incoming_packet.hpp"
#include "dummy/protocol/outgoing_packet.hpp"
#include "dummy/server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void TeleportMap::accept(ResponseVisitor& visitor) const
{
    visitor.visitResponse(*this);
}

void TeleportMap::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const
{
    pkt << m_status;
}

void TeleportMap::readFrom(Dummy::Protocol::IncomingPacket& pkt)
{
    pkt >> m_status;
}

std::shared_ptr<Response> TeleportMap::clone() const
{
    return std::make_shared<TeleportMap>(*this);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
