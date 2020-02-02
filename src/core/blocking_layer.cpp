#include "dummy/core/blocking_layer.hpp"

namespace Dummy {
namespace Core {

BlockingLayer::BlockingLayer(std::uint16_t width, std::uint16_t height)
    : std::vector<std::uint8_t>(width * height * 4),
      m_width(width*2),
      m_height(height*2)
{}

} // namespace Core
} // namespace Dummy
