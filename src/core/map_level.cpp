#include "core/map_level.hpp"

namespace Dummy {
namespace Core {

MapLevel::MapLevel(const GraphicMap& graphicMap)
    : m_graphicMap(graphicMap)
{}

void MapLevel::addLayer(std::int8_t position, GraphicLayer&& layer) {
    m_layers[position] = std::move(layer);
}

const GraphicLayer& MapLevel::graphicLayer(std::int8_t position) const {
    return m_layers.at(position);
}

} // namespace Core
} // namespace Dummy
