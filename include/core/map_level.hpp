#pragma once

#include <cstdint>
#include <map>
#include <vector>

using GraphicLayer = std::vector<std::pair<std::int8_t, std::int8_t>>;
using GraphicLayers = std::map<std::int8_t, GraphicLayer>;

namespace Dummy {
namespace Core {

class GraphicMap;

class MapLevel {
public:
    MapLevel(const GraphicMap&);
    void addLayer(std::int8_t, GraphicLayer&&);
    const GraphicLayer& layer(std::int8_t) const;
    const GraphicLayers& layers() const {
        return m_layers;
    }
    GraphicLayers& layers() {
        return m_layers;
    }
private:
    const GraphicMap& m_graphicMap;
    GraphicLayers m_layers;
};

} // namespace Core
} // namespace Dummy
