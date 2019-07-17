#include "core/blocking_layer.hpp"
#include "core/graphic_layer.hpp"
#include "local/map.hpp"
#include "local/level.hpp"


namespace Dummy {
namespace Local {

Level::Level(const Map& map)
    : m_map(map), m_blockingLayer(m_map.width(), m_map.height()) {}

void Level::addGraphicLayer(
    std::int8_t position,
    Dummy::Core::GraphicLayer&& layer
) {
    m_graphicLayers[position] = std::move(layer);
}

void Level::setBlockingLayer(Dummy::Core::BlockingLayer&& blockingLayer) {
    m_blockingLayer = std::move(blockingLayer);
}

std::uint16_t Level::width() const {
    return m_map.width();
}

std::uint16_t Level::height() const {
    return m_map.height();
}

} // namespace Local
} // namespace Dummy
