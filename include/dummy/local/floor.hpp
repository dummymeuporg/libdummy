#pragma once

#include <dummy/core/blocking_layer.hpp>
#include <dummy/core/graphic_layer.hpp>
#include <dummy/local/event.hpp>

#include <cstdint>
#include <map>
#include <memory>

namespace Dummy {

namespace Local {

class Map;

using Coords = std::pair<std::uint8_t, std::uint8_t>;
using GraphicLayers = std::map<std::int8_t, Dummy::Core::GraphicLayer>;
using Events = std::map<std::uint16_t, std::shared_ptr<Event>>;

class Floor {
public:
    Floor(const Map&);
    void addGraphicLayer(std::int8_t,
                         Dummy::Core::GraphicLayer&&);
    const Dummy::Core::GraphicLayer& graphicLayer(std::int8_t position) const {
        return m_graphicLayers.at(position);
    }
    GraphicLayers& graphicLayers() {
        return m_graphicLayers;
    }

    const GraphicLayers& graphicLayers() const {
        return m_graphicLayers;
    }

    Dummy::Core::BlockingLayer& blockingLayer() {
        return m_blockingLayer;
    }

    const Dummy::Core::BlockingLayer& blockingLayer() const {
        return m_blockingLayer;
    }

    std::uint16_t width() const;
    std::uint16_t height() const;

    const Map& map() const {
        return m_map;
    }

    void setBlockingLayer(Dummy::Core::BlockingLayer&&);

    bool isBlocking(std::uint16_t x, std::uint16_t y) const {
        return m_blockingLayer.isBlocking(x, y);
    }
    Events& touchEvents() {
        return m_touchEvents;
    }
protected:
    const Map& m_map;
    Dummy::Core::BlockingLayer m_blockingLayer;
    GraphicLayers m_graphicLayers;
    Events m_touchEvents;
};

} // namespace Local
} // namespace Dummy
