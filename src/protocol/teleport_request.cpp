#include "dummy/protocol/teleport_request.hpp"

namespace Dummy {
namespace Protocol {

TeleportRequest::TeleportRequest(const std::string& destinationMap,
                                 tilecoords pos, uint8_t floor,
                                 const std::string& destinationInstance)
    : m_destinationMap(destinationMap)
    , m_position(pos)
    , m_floor(floor)
    , m_destinationInstance(destinationInstance)
{}

} // namespace Protocol
} // namespace Dummy
