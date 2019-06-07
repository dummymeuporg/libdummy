#include "core/character.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/response/select_character.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void SelectCharacter::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void SelectCharacter::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const {
    pkt << m_status;
}

} // namespace Response
} // namespace Server
} // namespace Dummy
