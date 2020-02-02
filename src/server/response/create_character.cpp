#include "dummy/core/character.hpp"
#include "dummy/protocol/incoming_packet.hpp"
#include "dummy/protocol/outgoing_packet.hpp"
#include "dummy/server/response/create_character.hpp"
#include "dummy/server/response/response_visitor.hpp"

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
    pkt << m_status;
    if (0 == m_status) {
        pkt << *m_character;
    }
}

void CreateCharacter::readFrom(Dummy::Protocol::IncomingPacket& pkt) {
    pkt >> m_status;
    if (0 == m_status) {
        auto chr = std::make_shared<Dummy::Core::Character>();
        pkt >> *chr;
        setCharacter(chr);
    }
}

std::shared_ptr<Response> CreateCharacter::clone() const {
    return std::make_shared<CreateCharacter>(*this);
}

} // namespace Response
} // namespace Server
} // namespace Dummy
