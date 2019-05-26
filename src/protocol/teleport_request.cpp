#include "protocol/teleport_request.hpp"

namespace Dummy {

namespace Protocol {

TeleportRequest::TeleportRequest(
    const std::string& destinationMap,
    const std::pair<std::uint16_t, std::uint16_t>& pos
) : m_destinationMap(destinationMap), m_position(pos)
{
}

} // namespace Protocol

} // namespace Dummy
