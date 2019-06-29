#pragma once

#include <cstdint>
#include <map>
#include <vector>

using BlockingLayer = std::vector<std::uint8_t>;
using GraphicLayer = std::vector<std::pair<std::int8_t, std::int8_t>>;
using GraphicLayers = std::map<std::int8_t, GraphicLayer>;

namespace Dummy {
namespace Core {

class GraphicMap;

class MapLevel {
public:
    MapLevel(const GraphicMap&);
    void addLayer(std::int8_t, GraphicLayer&&);
    const GraphicLayer& graphicLayer(std::int8_t) const;
    const GraphicLayers& graphicLayers() const {
        return m_layers;
    }
    const BlockingLayer& blockingLayer() const {
        return m_blockingLayer;
    }
protected:
    const GraphicMap& m_graphicMap;
    BlockingLayer m_blockingLayer;
    GraphicLayers m_layers;
};

} // namespace Core
} // namespace Dummy
