#pragma once

#include <cstdint>
#include <map>
#include <memory>

#include "dummy/core/layer.hpp"
#include "dummy/local/event.hpp"

namespace Dummy {
namespace Local {

class Map;

using GraphicLayers = std::map<int8_t, Core::GraphicLayer>;
using Events        = std::map<uint16_t, std::shared_ptr<Event>>;

class Floor
{
public:
    Floor(const Map&);
    void addGraphicLayer(int8_t, Core::GraphicLayer&&);
    const Dummy::Core::GraphicLayer& graphicLayer(int8_t position) const
    {
        return m_graphicLayers.at(position);
    }
    GraphicLayers& graphicLayers() { return m_graphicLayers; }

    const GraphicLayers& graphicLayers() const { return m_graphicLayers; }

    Dummy::Core::BlockingLayer& blockingLayer() { return m_blockingLayer; }

    const Dummy::Core::BlockingLayer& blockingLayer() const
    {
        return m_blockingLayer;
    }

    uint16_t width() const;
    uint16_t height() const;

    const Map& map() const { return m_map; }

    void setBlockingLayer(Dummy::Core::BlockingLayer&&);

    bool isBlocking(tilecoords xy) const { return m_blockingLayer.at(xy); }

    Events& touchEvents() { return m_touchEvents; }

    const Events& touchEvents() const { return m_touchEvents; }

    Events& keypressEvents() { return m_keypressEvents; }

    const Events& keypressEvents() const { return m_keypressEvents; }


protected:
    const Map& m_map;
    Dummy::Core::BlockingLayer m_blockingLayer;
    GraphicLayers m_graphicLayers;
    Events m_touchEvents;
    Events m_keypressEvents;
};

} // namespace Local
} // namespace Dummy
