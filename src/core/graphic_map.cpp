#include <filesystem>
#include <fstream>
#include <iostream>

#include "core/graphic_map.hpp"
#include "core/project.hpp"

namespace fs = std::filesystem;

namespace Dummy
{

namespace Core
{

GraphicMap::GraphicMap(const Project& project, const std::string& name)
    : Map(project, name)
{
    std::cerr << "GraphicMap constructor" << std::endl;
}


void GraphicMap::_loadMapFile(std::ifstream& ifs) {
    Map::_loadMapFile(ifs);
    std::cerr << "GraphicMap::_loadMapFile" << std::endl;
    std::uint32_t strSize;
    
    /* Read chipset. */
    ifs.read(reinterpret_cast<char*>(&strSize), sizeof(std::uint32_t));
    if (0 != strSize) {
        m_chipset.resize(strSize);
        ifs.read(m_chipset.data(), strSize);
    } else {
        m_chipset = ""; // XXX should not happen. Throw exception?
    }

    std::cerr << "Chipset: " << m_chipset << std::endl;

    /* Read music */
    ifs.read(reinterpret_cast<char*>(&strSize), sizeof(std::uint32_t));
    if (0 != strSize) {
        m_music.resize(strSize);
        ifs.read(m_music.data(), strSize);
    } else {
        m_music = "";
    }

    /* Read layers. */
    std::size_t elements = m_width * m_height;

    // XXX: for now
    /*
    std::uint8_t levelsCount = 1;

    for (std::uint8_t i = 0; i < levelsCount; ++i) {
        _readMapLevel(ifs);
    }
    */

    m_firstLayer.resize(elements);
    ifs.read(
        reinterpret_cast<char*>(m_firstLayer.data()),
        static_cast<std::streamsize>(
            elements * sizeof(std::pair<std::int8_t, std::int8_t>)
        )
    );

    m_secondLayer.resize(elements);
    ifs.read(
         reinterpret_cast<char*>(m_secondLayer.data()),
         static_cast<std::streamsize>(
             elements * sizeof(std::pair<std::int8_t, std::int8_t>)
         )
     );

    m_thirdLayer.resize(elements);
    ifs.read(
         reinterpret_cast<char*>(m_thirdLayer.data()),
         static_cast<std::streamsize>(
             elements * sizeof(std::pair<std::int8_t, std::int8_t>)
         )
     );

    m_fourthLayer.resize(elements);
    ifs.read(
         reinterpret_cast<char*>(m_fourthLayer.data()),
         static_cast<std::streamsize>(
             elements * sizeof(std::pair<std::int8_t, std::int8_t>)
         )
     );

    // XXX: copy the layers into an home made level
    MapLevel mapLevel(*this);
    mapLevel.addLayer(-1, std::move(m_firstLayer));
    mapLevel.addLayer(0, std::move(m_secondLayer));
    mapLevel.addLayer(1, std::move(m_thirdLayer));
    mapLevel.addLayer(2, std::move(m_fourthLayer));
    m_mapLevels.push_back(mapLevel);
}

void GraphicMap::_readMapLevel(std::ifstream& ifs) {

}

} // namespace Core

} // namespace Dummy
