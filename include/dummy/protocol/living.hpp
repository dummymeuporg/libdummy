#pragma once

#include <cstdint>
#include <string>

#include <dummy/core/character.hpp>

namespace Dummy {

namespace Protocol {

class Living {
public:
    Living(std::uint16_t,
           std::uint16_t,
           std::uint8_t,
           const std::string&,
           Dummy::Core::Character::Direction);

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    const std::string& chipset() const {
        return m_chipset;
    }

    Dummy::Core::Character::Direction direction() const {
        return m_direction;
    }

    void setPosition(std::uint16_t, std::uint16_t);
    void setDirection(Dummy::Core::Character::Direction);
    void setChipset(const std::string&);

protected:
    std::uint16_t m_x;
    std::uint16_t m_y;
    std::uint8_t m_floor;
    std::string m_chipset;
    Dummy::Core::Character::Direction m_direction;
};

} // namespace Protocol

} // namespace Dummy
