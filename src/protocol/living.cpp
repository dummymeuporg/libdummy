#include <dummy/protocol/living.hpp>

namespace Dummy {

namespace Protocol {

Living::Living(std::uint16_t x,
               std::uint16_t y,
               const std::string& name,
               const std::string& chipset,
               Dummy::Core::Character::Direction direction)
    : m_x(x), m_y(y), m_name(name), m_chipset(chipset), m_direction(direction)
{
}

void Living::setPosition(std::uint16_t x, std::uint16_t y) {
    m_x = x;
    m_y = y;
}

void Living::setDirection(Dummy::Core::Character::Direction direction) {
    m_direction = direction;
}

void Living::setChipset(const std::string& chipset) {
    m_chipset = chipset;
}

void Living::setName(const std::string& name) {
    m_name = name;
}

} // namespace Protocol

} // namespace Dummy
