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

    const MapLevels& mapLevels() const {
        return m_mapLevels;
    }
protected:
    virtual void _loadMapFile(std::ifstream& ifs) override;
    void _readMapLevel(std::ifstream&);
protected:
    std::string m_chipset;
    std::string m_music;
    MapLevels m_mapLevels;
};

} // namespace Core

} // namespace Dummy
