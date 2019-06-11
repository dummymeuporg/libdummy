#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/response/set_position.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void SetPosition::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void SetPosition::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const {
    pkt << m_status;
}

void SetPosition::readFrom(Dummy::Protocol::IncomingPacket& pkt) {
    pkt >> m_status;
}

} // namespace Response
} // namespace Server
} // namespace Dummy
