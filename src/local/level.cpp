#include "local/level.hpp"


namespace Dummy {
namespace Local {

Level::Level(const Map& map) : m_map(map) {}

void Level::addGraphicLayer(
    std::int8_t position,
    GraphicLayer && layer
) {
    m_graphicLayers[position] = std::move(layer);
}

void Level::setBlockingLayer(BlockingLayer&& blockingLayer) {
    m_blockingLayer = std::move(blockingLayer);
}

} // namespace Local
} // namespace Dummy
