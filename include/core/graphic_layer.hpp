#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {
class GraphicLayer : public std::vector<std::pair<std::int8_t, std::int8_t>> {
public:
    GraphicLayer(std::uint16_t, std::uint16_t);
};

} // namespace Core
} // namespace Dummy
