#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {

class GraphicLayer : public std::vector<std::pair<std::int8_t, std::int8_t>>
{
public:
    GraphicLayer(std::uint16_t = 1, std::uint16_t = 1);

    std::uint16_t width() const { return m_width; }
    std::uint16_t height() const { return m_height; }

private:
    std::uint16_t m_width;
    std::uint16_t m_height;
};

} // namespace Core
} // namespace Dummy
