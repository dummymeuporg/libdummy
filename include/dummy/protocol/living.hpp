#pragma once

#include <cstdint>
#include <string>

#include "dummy/core/character.hpp"

namespace Dummy {
namespace Protocol {

class Living
{
public:
    Living(uint32_t, tilecoords, uint8_t, const std::string&,
           Dummy::Core::Character::Direction);

    uint32_t id() const { return m_id; }
    tilecoords pos() const { return m_xy; }
    const std::string& chipset() const { return m_chipset; }
    Dummy::Core::Character::Direction direction() const { return m_direction; }

    void setPosition(tilecoords);
    void setDirection(Dummy::Core::Character::Direction);
    void setChipset(const std::string&);

protected:
    uint32_t m_id;
    tilecoords m_xy;
    uint8_t m_floor;
    std::string m_chipset;
    Dummy::Core::Character::Direction m_direction;
};

} // namespace Protocol
} // namespace Dummy
