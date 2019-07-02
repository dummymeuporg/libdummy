#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {
class BlockingLayer : public std::vector<std::uint8_t>{
public:
    BlockingLayer(std::uint16_t = 1, std::uint16_t = 1);
};

} // namespace Core
} // namespace Dummy
