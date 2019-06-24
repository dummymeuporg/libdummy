#pragma once

#include "core/map.hpp"
#include "core/map_level.hpp"

namespace Dummy
{

namespace Core
{

using GraphicLayer = std::vector<std::pair<std::int8_t, std::int8_t>>;
using MapLevels = std::vector<MapLevel>;

class GraphicMap : public Map {
public:
    GraphicMap(const Project&, const std::string&);
    const std::string& chipset() const {
        return m_chipset;
    }

    const std::string& music() const {
        return m_music;
    }

    const GraphicLayer& firstLayer() const {
        return m_firstLayer;
    }

    const GraphicLayer& secondLayer() const {
        return m_secondLayer;
    }

    const GraphicLayer& thirdLayer() const {
        return m_thirdLayer;
    }

    const GraphicLayer& fourthLayer() const {
        return m_fourthLayer;
    }
protected:
    virtual void _loadMapFile(std::ifstream& ifs) override;
    void _readMapLevel(std::ifstream&);
protected:
    std::string m_chipset;
    std::string m_music;
    GraphicLayer m_firstLayer;
    GraphicLayer m_secondLayer;
    GraphicLayer m_thirdLayer;
    GraphicLayer m_fourthLayer;
    MapLevels m_mapLevels;
};

} // namespace Core

} // namespace Dummy
