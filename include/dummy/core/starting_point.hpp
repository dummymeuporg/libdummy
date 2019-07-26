#pragma once

#include <cstdint>
#include <string>


namespace Dummy {
namespace Core {

class StartingPoint {
public:
    StartingPoint(
        const std::string&,
        const std::pair<std::uint16_t, std::uint16_t>&,
        std::uint8_t
    );

    const std::string& mapName() const {
        return m_mapName;
    }

    const std::pair<std::uint16_t, std::uint16_t>& position() const {
        return m_position;
    }

    std::uint8_t floor() const {
        return m_floor;
    }
private:
    std::string m_mapName;
    std::pair<std::uint16_t, std::uint16_t> m_position;
    std::uint8_t m_floor;
};

} // namespace Core
} // namespace Dummy