#pragma once

#include <cstdint>
#include <string>

namespace Dummy {

namespace Protocol {

class Living {
public:
    Living(std::uint16_t,
           std::uint16_t,
           const std::string&,
           const std::string&);

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
    std::string m_name;
    std::string m_chipset;
};

} // namespace Protocol

} // namespace Dummy
