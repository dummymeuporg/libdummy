#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "server/response/characters_list_response.hpp"
#include "server/response/response_visitor.hpp"

namespace Dummy {
namespace Server {
namespace Response {

void CharactersListResponse::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void
CharactersListResponse::addCharacter(
    std::shared_ptr<Dummy::Core::Character> character
)
{
    m_charactersList.push_back(character);
}

void CharactersListResponse::serializeTo(Dummy::Protocol::OutgoingPacket& pkt)
const
{
    pkt << static_cast<std::uint16_t>(m_charactersList.size());
    for (auto chr: m_charactersList) {
        pkt << *chr;
    }
}

void CharactersListResponse::readFrom(Dummy::Protocol::IncomingPacket& pkt) {
    pkt >> m_status;
    // XXX: extract characters
}

} // namespace Response
} // namespace Server
} // namespace Dummy
