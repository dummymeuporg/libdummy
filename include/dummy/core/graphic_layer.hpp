#pragma once

#include <cstdint>
#include <vector>
#include "dummy/utils/dummy_types.hpp"

namespace Dummy {
namespace Core {

class GraphicLayer : public std::vector<tileaspect>
{
public:
    GraphicLayer(uint16_t w = 1, uint16_t h = 1);

    uint16_t width() const { return m_width; }
    uint16_t height() const { return m_height; }

private:
    uint16_t m_width;
    uint16_t m_height;
};

} // namespace Core
} // namespace Dummy
