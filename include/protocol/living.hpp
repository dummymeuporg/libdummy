#pragma once

#include <cstdint>

namespace Dummy {

namespace Protocol {

class Living {
public:
    Living(std::uint16_t, std::uint16_t, const std::string&);

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    void setPosition(std::uint16_t, std::uint16_t);

protected:
    std::uint16_t m_x;
    std::uint16_t m_y;
    std::string m_chipset, m_name;
};

} // namespace Protocol

} // namespace Dummy
