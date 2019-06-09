#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "protocol/character_off.hpp"

namespace Dummy {

namespace Protocol {

CharacterOff::CharacterOff(const std::string& name) : m_name(name) {}

void CharacterOff::_streamToPacket(OutgoingPacket& pkt) const {
    pkt << m_name;
}

void CharacterOff::_streamFromPacket(IncomingPacket& pkt) {
    pkt >> m_name;
}

} // namespace Protocol

} // namespace Dummy
