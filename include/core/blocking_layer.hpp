#pragma once

#include <cstdint>
#include <vector>

namespace Dummy {
namespace Core {
class BlockingLayer : public std::vector<std::uint8_t>{
public:
    BlockingLayer(std::uint16_t, std::uint16_t);
};

} // namespace Core
} // namespace Dummy
