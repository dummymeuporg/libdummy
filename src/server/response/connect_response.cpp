#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/response/connect_response.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void ConnectResponse::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void ConnectResponse::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const {
    pkt << m_status;
}


void ConnectResponse::readFrom(Dummy::Protocol::IncomingPacket& pkt) {
    pkt >> m_status;
}

} // namespace Response
} // namespace Server
} // namespace Dummy
