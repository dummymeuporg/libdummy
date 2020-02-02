#pragma once

#include <cstdint>
#include <vector>

#include "dummy/utils/dummy_types.hpp"

namespace Dummy {
namespace Core {

class BlockingLayer : public std::vector<uint8_t>
{
public:
    BlockingLayer(uint16_t w = 1, uint16_t h = 1);

    uint16_t width() const { return m_width; }
    uint16_t height() const { return m_height; }
    bool isBlocking(tilecoords xy) const
    {
        return operator[](xy.second* m_width + xy.first);
    }
    bool isBlocking(unsigned i) const { return operator[](i); }

private:
    uint16_t m_width;
    uint16_t m_height;
};

} // namespace Core
} // namespace Dummy
