#include "dummy/core/graphic_layer.hpp"

namespace Dummy {
namespace Core {

GraphicLayer::GraphicLayer(uint16_t width, uint16_t height)
    : std::vector<tileaspect>(width * height, {-1, -1})
    , m_width(width)
    , m_height(height)
{}

} // namespace Core
} // namespace Dummy
