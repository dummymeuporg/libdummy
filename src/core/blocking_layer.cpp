#include "dummy/core/blocking_layer.hpp"

namespace Dummy {
namespace Core {

BlockingLayer::BlockingLayer(uint16_t width, uint16_t height)
    : std::vector<uint8_t>(width * height * 4, false)
    , m_width(width * 2)
    , m_height(height * 2)
{}

} // namespace Core
} // namespace Dummy
