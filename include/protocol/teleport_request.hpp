#pragma once

#include <cstdint>
#include <string>

namespace Dummy {

namespace Protocol {

class TeleportRequest {
public:
    TeleportRequest(const std::string&,
                    const std::pair<std::uint16_t, std::uint16_t>&);
private:
    std::string m_destinationMap;
    std::pair<std::uint16_t, std::uint16_t> m_position;
};

} // namespace Protocol

} // namespace Dummy
