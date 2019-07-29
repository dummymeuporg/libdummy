#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/server/response/message.hpp>
#include <dummy/server/response/response_visitor.hpp>


namespace Dummy {
namespace Server {
namespace Response {

void Message::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void Message::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const {
    pkt << m_status << m_author << m_content;
}

void Message::readFrom(Dummy::Protocol::IncomingPacket& pkt) {
    pkt >> m_status >> m_author >> m_content;
}

void Message::setAuthor(const std::string& author) {
   m_author = author;
}

void Message::setContent(const std::string& content) {
    m_content = content;
}

} // namespace Response
} // namepsace Server
} // namespace Dummy
