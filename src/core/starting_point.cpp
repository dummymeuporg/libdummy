#include <dummy/core/starting_point.hpp>

namespace Dummy {
namespace Core {

StartingPoint::StartingPoint(
    const std::string& mapName,
    const std::pair<std::uint16_t, std::uint16_t>& position,
    std::uint8_t floor,
    const std::string& instance
) : m_mapName(mapName), m_position(position), m_floor(floor),
    m_instance(instance)
{}

} // namespace Core
} // namespace Dummy
