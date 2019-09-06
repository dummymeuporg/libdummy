#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

#include <dummy/core/graphic_layer.hpp>

#include <dummy/local/map.hpp>
#include <dummy/local/project.hpp>

namespace fs = std::filesystem;

namespace Dummy
{

namespace Local
{

Map::Map(const Project& project, const std::string& name)
    : Dummy::Core::Map(name), m_project(project)
{
    std::cerr << "Local map constructor" << std::endl;
}

void Map::load() {
    fs::path basePath(m_project.projectPath() / "maps");
    std::string mapFile(m_name + ".map");
    std::string blkFile(m_name + ".blk");
    std::string luaFile(m_name + ".lua");

    std::ifstream ifsMapFile(basePath / mapFile, std::ios::binary);
    if (!ifsMapFile.is_open()) {
        throw Dummy::Core::MapFileNotFound();
    }

    std::ifstream ifsBlkFile(basePath / blkFile, std::ios::binary);
    if (!ifsBlkFile.is_open()) {
        throw Dummy::Core::BlkFileNotFound();
    }
    loadMapFile(ifsMapFile);
    readBlkFile(ifsBlkFile);
    loadLuaFile((basePath / luaFile).string());

    for (int i = 0; i < m_floorsCount; ++i) {
        readMapFloor(ifsMapFile, ifsBlkFile);
    }
}

void Map::loadMapFile(std::ifstream& ifs) {
    Dummy::Core::Map::loadBaseInfo(ifs);
    std::cerr << "Map::loadMapFile" << std::endl;
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
}

void Map::readMapFloor(
    std::ifstream& ifsMapFile,
    std::ifstream& ifsBlkFile)
{
    Floor floor(*this);
    std::size_t elements = m_width * m_height;
    std::uint8_t layersCount;

    // Read layers count
    ifsMapFile.read(
        reinterpret_cast<char*>(&layersCount),
        sizeof(std::uint8_t)
    );

    for(std::uint8_t i = 0; i < layersCount; i++) {
        // Read the layer position
        std::int8_t position;
        ifsMapFile.read(
            reinterpret_cast<char*>(&position), sizeof(std::uint8_t)
        );
        Dummy::Core::GraphicLayer graphicLayer(m_width, m_height);
        // read the whole layer
        ifsMapFile.read(
            reinterpret_cast<char*>(graphicLayer.data()),
            static_cast<std::streamsize>(
                elements * sizeof(std::pair<std::int8_t, std::int8_t>)
            )
        );
        floor.addGraphicLayer(position, std::move(graphicLayer));
    }
    // Read the blocking layer
    Dummy::Core::BlockingLayer&& blockingLayer = loadBlockingLayer(ifsBlkFile);
    floor.setBlockingLayer(std::move(blockingLayer));

    // Create the floor.
    m_floors.push_back(std::move(floor));
}

} // namespace Core
} // namespace Dummy
