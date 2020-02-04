#include "dummy/local/floor.hpp"

#include "dummy/local/map.hpp"

namespace Dummy {
namespace Local {

Floor::Floor(const Map& map)
    : m_map(map)
    , m_blockingLayer(m_map.width() * 2, m_map.height() * 2, false)
{}

void Floor::addGraphicLayer(int8_t position, Dummy::Core::GraphicLayer&& layer)
{
    m_graphicLayers[position] = std::move(layer);
}

void Floor::setBlockingLayer(Dummy::Core::BlockingLayer&& blockingLayer)
{
    m_blockingLayer = std::move(blockingLayer);
}

uint16_t Floor::width() const
{
    return m_map.width();
}

uint16_t Floor::height() const
{
    return m_map.height();
}

} // namespace Local
} // namespace Dummy
