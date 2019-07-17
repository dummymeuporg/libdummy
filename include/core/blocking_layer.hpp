#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {
class BlockingLayer : public std::vector<std::uint8_t> {
public:
    BlockingLayer(std::uint16_t = 1, std::uint16_t = 1);

    std::uint16_t width() const {
        return m_width;
    }

    std::uint16_t height() const {
        return m_height;
    }

    bool isBlocking(std::uint16_t x, std::uint16_t y) const {
        return operator[](y * m_width + x);
    }
private:
    std::uint16_t m_width;
    std::uint16_t m_height;
};

} // namespace Core
} // namespace Dummy
