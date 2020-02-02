#pragma once

#include <cstdint>
#include <string>

#include "dummy/utils/dummy_types.hpp"

namespace Dummy {
namespace Protocol {

class TeleportRequest
{
public:
    TeleportRequest(const std::string&, tilecoords, uint8_t,
                    const std::string&);

    const std::string& destinationMap() const { return m_destinationMap; }

    const std::string& destinationInstance() const
    {
        return m_destinationInstance;
    }

    tilecoords position() const { return m_position; }

    uint8_t floor() const { return m_floor; }

private:
    std::string m_destinationMap;
    tilecoords m_position;
    uint8_t m_floor;
    std::string m_destinationInstance;
};

} // namespace Protocol
} // namespace Dummy
