#include "dummy/protocol/living.hpp"

namespace Dummy {
namespace Protocol {

Living::Living(std::uint32_t id, std::uint16_t x, std::uint16_t y,
               std::uint8_t floor, const std::string& chipset,
               Dummy::Core::Character::Direction direction)
    : m_id(id)
    , m_x(x)
    , m_y(y)
    , m_floor(floor)
    , m_chipset(chipset)
    , m_direction(direction)
{}

void Living::setPosition(std::uint16_t x, std::uint16_t y)
{
    m_x = x;
    m_y = y;
}

void Living::setDirection(Dummy::Core::Character::Direction direction)
{
    m_direction = direction;
}

void Living::setChipset(const std::string& chipset)
{
    m_chipset = chipset;
}

} // namespace Protocol
} // namespace Dummy
