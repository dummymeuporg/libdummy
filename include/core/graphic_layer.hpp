#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {
class GraphicLayer : public std::vector<std::pair<std::int8_t, std::int8_t>> {
public:
    GraphicLayer(std::uint16_t = 1, std::uint16_t = 1);
};

} // namespace Core
} // namespace Dummy
