#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/server/response/change_character.hpp>
#include <dummy/server/response/response_visitor.hpp>


namespace Dummy {
namespace Server {
namespace Response {

ChangeCharacter::ChangeCharacter() {}

void ChangeCharacter::accept(ResponseVisitor& visitor) const {
    visitor.visitResponse(*this);
}

void ChangeCharacter::serializeTo(Dummy::Protocol::OutgoingPacket& pkt) const {
    pkt << m_status << m_mapLocation << m_position.first
        << m_position.second;
}

void ChangeCharacter::readFrom(Dummy::Protocol::IncomingPacket& pkt) {
    pkt >> m_status >> m_mapLocation >> m_position.first
        >> m_position.second;
}

void ChangeCharacter::setMapLocation(const std::string& mapLocation) {
    m_mapLocation = mapLocation;
}

void ChangeCharacter::setPosition(const Position& position) {
    m_position = position;
}

} // namespace Response
} // namespace Server
} // namespace Dummy
