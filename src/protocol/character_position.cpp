#include "protocol/incoming_packet.hpp"
#include "protocol/outgoing_packet.hpp"
#include "protocol/character_position.hpp"

namespace Dummy {

namespace Protocol {

CharacterPosition::CharacterPosition(
    std::uint16_t x,
    std::uint16_t y,
    const std::string& name,
    const std::string& chipset
) : m_x(x), m_y(y), m_name(name), m_chipset(chipset)
{
}

void CharacterPosition::_streamToPacket(OutgoingPacket& outPkt) const {
    outPkt << m_x << m_y << m_name << m_chipset;
}

void CharacterPosition::_streamFromPacket(IncomingPacket& inPkt) {
    inPkt >> m_x >> m_y >> m_name >> m_chipset;
}

} // namespace Protocol

} // namespace Dummy
