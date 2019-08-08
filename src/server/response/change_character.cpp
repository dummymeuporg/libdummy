#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/server/response/change_character.hpp>
#include <dummy/server/response/response_visitor.hpp>


namespace Dummy {
namespace Server {
namespace Response {

void ChangeCharacter::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void ChangeCharacter::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const {
    pkt << m_status;
}

void ChangeCharacter::readFrom(Dummy::Protocol::IncomingPacket& pkt) {
    pkt >> m_status;
}


} // namespace Response
} // namespace Server
} // namespace Dummy
