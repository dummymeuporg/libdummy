#pragma once

#include <cstdint>
#include <string>

namespace Dummy {

namespace Protocol {

class TeleportRequest {
public:
    TeleportRequest(const std::string&,
                    const std::pair<std::uint16_t, std::uint16_t>&,
                    const std::string&);

    const std::string& destinationMap() const {
        return m_destinationMap;
    }

    const std::string& destinationInstance() const {
        return m_destinationInstance;
    }

    const std::pair<std::uint16_t, std::uint16_t>& position() const {
        return m_position;
    }
private:
    std::string m_destinationMap;
    std::pair<std::uint16_t, std::uint16_t> m_position;
    std::string m_destinationInstance;
};

} // namespace Protocol

} // namespace Dummy
