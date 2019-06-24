#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

#include "core/map.hpp"
#include "core/project.hpp"

namespace fs = std::filesystem;

namespace Dummy
{

namespace Core
{

Map::Map(const Project& project, const std::string& name)
    : m_project(project), m_name(name)
{
    m_blockingLevels.resize(1); // One level at least.
}

void Map::load() {
    std::cerr << "load map" << std::endl;
    fs::path basePath(m_project.projectPath() / "maps");
    std::cerr << "path: " << basePath.string() << std::endl;
    std::string mapFile(m_name + ".map");
    std::string blkFile(m_name + ".blk");

    _internalLoadMapFile((basePath / mapFile).string());
    _loadBlkFile((basePath / blkFile).string());
}

void Map::_internalLoadMapFile(std::string fullpath) {
    std::ifstream ifs(fullpath, std::ios::binary);
    if (!ifs.is_open()) {
        throw MapFileNotFound();
    }
    _loadMapFile(ifs); 
    ifs.close();
}

void Map::_loadMapFile(std::ifstream& ifs) {
    std::cerr << "Map::_loadMapFile" << std::endl;
    std::uint32_t magicNumber;
    std::uint16_t version;
    ifs.read(reinterpret_cast<char*>(&magicNumber), sizeof(std::uint32_t));
    if (magicNumber != Map::MAP_MAGIC_WORD) {
        throw WrongMagicNumber();
    }

    // XXX what to do with version?
    ifs.read(reinterpret_cast<char*>(&version), sizeof(std::uint16_t));

    // read dimensions
    ifs.read(reinterpret_cast<char*>(&m_width), sizeof(std::uint16_t));
    ifs.read(reinterpret_cast<char*>(&m_height), sizeof(std::uint16_t));
    std::cerr << m_name << " (" << m_width * 2 << "," << m_height * 2 << ")"
        << std::endl;

    // read the number of levels
    ifs.read(reinterpret_cast<char*>(&m_levelsCount), sizeof(std::uint8_t));

}

void Map::_loadBlkFile(std::string fullpath)
{
    std::uint32_t magicNumber;
    std::ifstream ifs(fullpath, std::ios::binary);
    if (!ifs.is_open()) {
        throw BlkFileNotFound();
    }
    ifs.read(reinterpret_cast<char*>(&magicNumber), sizeof(std::uint32_t));
    if (magicNumber != Map::BLK_MAGIC_WORD) {
        throw WrongMagicNumber();
    }

    for (unsigned long long i = 0; i < m_levelsCount; ++i) {
        BlockingLayer blockingLayer(m_width * m_height * 2);
        //m_blockingLayer.resize(m_width * m_height * 2);
        ifs.read(
            reinterpret_cast<char*>(blockingLayer.data()),
            blockingLayer.size() * sizeof(std::uint8_t)
        );
        addBlockingLevel(std::move(blockingLayer));
        std::cerr << m_name << " read blocking layer." << std::endl;
    }
}

bool Map::isBlocking(std::uint16_t x, std::uint16_t y) const {
    return static_cast<bool>(m_blockingLevels[0][y * (m_width * 2) + x]);
}

void Map::addBlockingLevel(BlockingLayer&& blockingLayer) {
    m_blockingLevels.push_back(std::move(blockingLayer));
}

} // namespace Core

} // namespace Dummy
