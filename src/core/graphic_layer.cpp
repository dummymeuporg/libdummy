#include "core/graphic_layer.hpp"

namespace Dummy {
namespace Core {

GraphicLayer::GraphicLayer(std::uint16_t width, std::uint16_t height)
    : std::vector<std::pair<std::int8_t, std::int8_t>>(width * height)
{}


} // namespace Core
} // namespace Dummy
