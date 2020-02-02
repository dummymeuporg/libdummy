#pragma once

#include <cstdint>
#include <string>

#include "dummy/utils/dummy_types.hpp"

namespace Dummy {
namespace Core {

class StartingPoint
{
public:
    StartingPoint(const std::string&, tilecoords, uint8_t,
                  const std::string& = "main");

    const std::string& mapName() const { return m_mapName; }
    tilecoords position() const { return m_position; }
    uint8_t floor() const { return m_floor; }
    const std::string& instance() const { return m_instance; }

private:
    std::string m_mapName;
    tilecoords m_position;
    uint8_t m_floor;
    std::string m_instance;
};

} // namespace Core
} // namespace Dummy
