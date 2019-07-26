#pragma once

#include <cstdint>
#include <string>

namespace Dummy {

namespace Protocol {

class TeleportRequest {
public:
    TeleportRequest(const std::string&,
                    const std::pair<std::uint16_t, std::uint16_t>&,
                    const std::string&,
                    std::uint8_t = 0);

    const std::string& destinationMap() const {
        return m_destinationMap;
    }

    const std::string& destinationInstance() const {
        return m_destinationInstance;
    }

    const std::pair<std::uint16_t, std::uint16_t>& position() const {
        return m_position;
    }

    std::uint8_t floor() const {
        return m_floor;
    }
private:
    std::string m_destinationMap;
    std::pair<std::uint16_t, std::uint16_t> m_position;
    std::uint8_t m_floor;
    std::string m_destinationInstance;
};

} // namespace Protocol

} // namespace Dummy
