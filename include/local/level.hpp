#pragma once

#include <cstdint>
#include <map>
#include <vector>

namespace Dummy {
namespace Local {

class Map;

using BlockingLayer = std::vector<std::uint8_t>;
using GraphicLayer = std::vector<std::pair<std::int8_t, std::int8_t>>;
using GraphicLayers = std::map<std::int8_t, GraphicLayer>;

class Level {
public:
    Level(const Map&);
    void addGraphicLayer(std::int8_t, GraphicLayer&&);
    const GraphicLayer& graphicLayer(std::int8_t position) const {
        return m_graphicLayers.at(position);
    }
    const GraphicLayers& graphicLayers() const {
        return m_graphicLayers;
    }
    const BlockingLayer& blockingLayer() const {
        return m_blockingLayer;
    }
    void setBlockingLayer(BlockingLayer&&);
protected:
    const Map& m_map;
    BlockingLayer m_blockingLayer;
    GraphicLayers m_graphicLayers;
};

} // namespace Local
} // namespace Dummy
