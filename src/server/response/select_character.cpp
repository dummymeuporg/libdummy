#include "dummy/server/response/select_character.hpp"

#include "dummy/protocol/incoming_packet.hpp"
#include "dummy/protocol/outgoing_packet.hpp"
#include "dummy/server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void SelectCharacter::accept(ResponseVisitor& visitor) const
{
    visitor.visitResponse(*this);
}

void SelectCharacter::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const
{
    pkt << m_status;
}

void SelectCharacter::readFrom(Dummy::Protocol::IncomingPacket& pkt)
{
    pkt >> m_status;
}

std::shared_ptr<Response> SelectCharacter::clone() const
{
    return std::make_shared<SelectCharacter>(*this);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
