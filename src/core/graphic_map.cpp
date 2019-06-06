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
    std::size_t bytesToRead = m_width * m_height * 2 * sizeof(std::int8_t);

    m_firstLayer.resize(bytesToRead);
    ifs.read(reinterpret_cast<char*>(m_firstLayer.data()), bytesToRead);

    m_secondLayer.resize(bytesToRead);
    ifs.read(reinterpret_cast<char*>(m_secondLayer.data()), bytesToRead);

    m_thirdLayer.resize(bytesToRead);
    ifs.read(reinterpret_cast<char*>(m_thirdLayer.data()), bytesToRead);

    m_fourthLayer.resize(bytesToRead);
    ifs.read(reinterpret_cast<char*>(m_fourthLayer.data()), bytesToRead);
}

} // namespace Core

} // namespace Dummy
