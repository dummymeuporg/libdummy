#pragma once

#include <string>

namespace Dummy {
namespace Core {

class Foe {
public:
    Foe(const std::string&, std::uint16_t, std::uint16_t, std::uint8_t);
    Foe(const std::string&,
        const std::pair<std::uint16_t, std::uint16_t>&,
        std::uint8_t);

    const std::string& chipset() const {
        return m_chipset;
    }

    const std::pair<std::uint16_t, std::uint16_t>& position() const {
        return m_position;
    }

    std::uint8_t floor() {
        return m_floor;
    }

private:
    std::string m_chipset;
    std::pair<std::uint16_t, std::uint16_t> m_position;
    std::uint8_t m_floor;
};

} // namespace Core
} // namespace Dummy
