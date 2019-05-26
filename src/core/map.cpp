#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

#include "core/map.hpp"
#include "core/project.hpp"

namespace fs = boost::filesystem;

namespace Dummy
{

namespace Core
{

Map::Map(const Project& project, const std::string& name)
    : m_project(project), m_name(name)
{
    fs::path basePath(project.projectPath() / "maps");
    std::string mapFile(name + ".map");
    std::string blkFile(name + ".blk");

    _internalLoadMapFile(std::move((basePath / mapFile).string()));
    _loadBlkFile(std::move((basePath / blkFile).string()));
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

    m_blocking.resize(m_width * m_height * 4);
    ifs.read(reinterpret_cast<char*>(m_blocking.data()),
            m_blocking.size() * sizeof(std::uint8_t));
    std::cerr << m_name << " read blocking layer." << std::endl;
}

} // namespace Core

} // namespace Dummy
