#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>
#include <dummy/protocol/map_update/map_update_visitor.hpp>
#include <dummy/protocol/map_update/character_off.hpp>

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

CharacterOff::CharacterOff(const std::string& name) : m_name(name) {}

void CharacterOff::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

void
CharacterOff::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {
    packet << m_name;
}

void CharacterOff::readFrom(Dummy::Protocol::IncomingPacket& packet) {
    packet >> m_name;
}



} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
