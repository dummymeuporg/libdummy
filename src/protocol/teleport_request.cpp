#include "protocol/map_update/teleport_request.hpp"

namespace Dummy {

namespace Protocol {

TeleportRequest::TeleportRequest(
    const std::string& destinationMap,
    const std::pair<std::uint16_t, std::uint16_t>& pos,
    const std::string& destinationInstance
) : m_destinationMap(destinationMap), m_position(pos),
    m_destinationInstance(destinationInstance)
{
}

} // namespace Protocol

} // namespace Dummy
