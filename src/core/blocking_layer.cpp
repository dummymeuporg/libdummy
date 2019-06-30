#include "core/blocking_layer.hpp"

namespace Dummy {
namespace Core {

BlockingLayer::BlockingLayer(std::uint16_t width, std::uint16_t height)
    : std::vector<std::uint8_t>(width * height * 2) {}

} // namespace Core
} // namespace Dummy
