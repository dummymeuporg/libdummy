#include "dummy/local/floor.hpp"
#include "dummy/core/blocking_layer.hpp"
#include "dummy/core/graphic_layer.hpp"
#include "dummy/local/map.hpp"

namespace Dummy {
namespace Local {

Floor::Floor(const Map& map)
    : m_map(map)
    , m_blockingLayer(m_map.width(), m_map.height())
{}

void Floor::addGraphicLayer(std::int8_t position,
                            Dummy::Core::GraphicLayer&& layer)
{
    m_graphicLayers[position] = std::move(layer);
}

void Floor::setBlockingLayer(Dummy::Core::BlockingLayer&& blockingLayer)
{
    m_blockingLayer = std::move(blockingLayer);
}

std::uint16_t Floor::width() const
{
    return m_map.width();
}

std::uint16_t Floor::height() const
{
    return m_map.height();
}

} // namespace Local
} // namespace Dummy
