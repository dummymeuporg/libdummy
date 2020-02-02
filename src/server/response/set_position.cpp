#include "dummy/server/response/set_position.hpp"
#include "dummy/protocol/incoming_packet.hpp"
#include "dummy/protocol/outgoing_packet.hpp"
#include "dummy/server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void SetPosition::accept(ResponseVisitor& visitor) const
{
    visitor.visitResponse(*this);
}

void SetPosition::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const
{
    pkt << m_status;
}

void SetPosition::readFrom(Dummy::Protocol::IncomingPacket& pkt)
{
    pkt >> m_status;
}

std::shared_ptr<Response> SetPosition::clone() const
{
    return std::make_shared<SetPosition>(*this);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
