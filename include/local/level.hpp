#pragma once

#include "core/blocking_layer.hpp"

#include <cstdint>
#include <map>
#include <memory>

namespace Dummy {
namespace Core {
class GraphicLayer;
}
namespace Local {

class Map;

using GraphicLayers = std::map<
    std::int8_t, std::unique_ptr<Dummy::Core::GraphicLayer>
>;

class Level {
public:
    Level(const Map&);
    void addGraphicLayer(std::int8_t, Dummy::Core::GraphicLayer&&);
    const Dummy::Core::GraphicLayer& graphicLayer(std::int8_t position) const {
        return *(m_graphicLayers.at(position));
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

    void setBlockingLayer(Dummy::Core::BlockingLayer&&);
protected:
    const Map& m_map;
    Dummy::Core::BlockingLayer m_blockingLayer;
    GraphicLayers m_graphicLayers;
};

} // namespace Local
} // namespace Dummy
