#include "protocol/living.hpp"

namespace Dummy {

namespace Protocol {

Living::Living(std::uint16_t x, std::uint16_t y, const std::string& name)
    : m_x(x), m_y(y), m_name(name)
{
}

void Living::setPosition(std::uint16_t x, std::uint16_t y) {
    m_x = x;
    m_y = y;
}

} // namespace Protocol

} // namespace Dummy
