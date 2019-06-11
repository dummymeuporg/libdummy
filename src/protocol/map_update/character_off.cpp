#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "protocol/map_update/map_update_visitor.hpp"
#include "protocol/map_update/character_off.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

CharacterOff::CharacterOff(const std::string& name) : m_name(name) {}

void CharacterOff::accept(MapUpdateVisitor& visitor) const {
    visitor.visitMapUpdate(*this);
}

void
CharacterOff::serializeTo(Dummy::Protocol::OutgoingPacket& packet) const {

}

void CharacterOff::readFrom(Dummy::Protocol::IncomingPacket& packet) {

}



} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
