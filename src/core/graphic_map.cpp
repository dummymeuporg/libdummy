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

    /* read levels count */
    ifs.read(reinterpret_cast<char*>(&m_levelsCount), sizeof(std::uint8_t));

    for(std::uint8_t i = 0; i < m_levelsCount; ++i) {
        _readMapLevel(ifs);
    }

}

void GraphicMap::_readMapLevel(std::ifstream& ifs) {
    MapLevel mapLevel(*this);
    std::size_t elements = m_width * m_height;
    std::uint8_t layersCount;

    // Read layers count
    ifs.read(reinterpret_cast<char*>(&layersCount), sizeof(std::uint8_t));

    for(std::uint8_t i = 0; i < layersCount; i++) {
        // Read the layer position
        std::int8_t position;
        ifs.read(
            reinterpret_cast<char*>(&position), sizeof(std::uint8_t)
        );
        GraphicLayer graphicLayer(elements);
        // read the whole layer
        ifs.read(
            reinterpret_cast<char*>(graphicLayer.data()),
            static_cast<std::streamsize>(
                elements * sizeof(std::pair<std::int8_t, std::int8_t>)
            )
        );
        mapLevel.addLayer(position, std::move(graphicLayer));
    }
    m_mapLevels.push_back(std::move(mapLevel));
}

} // namespace Core

} // namespace Dummy
