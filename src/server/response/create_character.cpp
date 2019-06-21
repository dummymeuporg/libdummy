#include "core/character.hpp"
#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/response/create_character.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void CreateCharacter::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void
CreateCharacter::setCharacter(std::shared_ptr<Dummy::Core::Character> chr) {
    m_character = chr;
}

void
CreateCharacter::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const {
    pkt << m_status << *chr;
}

void CreateCharacter::readFrom(Dummy::Protocol::IncomingPacket& pkt) {
    pkt >> m_status;
    auto chr = std::make_shared<Dummy::Core::Character>();
    pkt >> *chr;
    setCharacter(chr);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
