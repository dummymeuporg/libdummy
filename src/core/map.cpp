#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>

#include "core/blocking_layer.hpp"
#include "core/map.hpp"
#include "core/project.hpp"

namespace fs = std::filesystem;

namespace Dummy
{

namespace Core
{

Map::Map(const std::string& name) : m_name(name), m_width(1), m_height(1),
    m_levelsCount(0)
{
}

void Map::loadBaseInfo(std::ifstream& ifs) {
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

BlockingLayer Map::loadBlockingLayer(std::ifstream& ifs) {
    BlockingLayer layer(m_width, m_height);
    ifs.read(
        reinterpret_cast<char*>(layer.data()),
        static_cast<std::streamsize>(layer.size() * sizeof(std::uint8_t))
    );
    return layer;
}

void Map::readBlkFile(std::ifstream& ifs) {
    std::uint32_t magicNumber;

    ifs.read(reinterpret_cast<char*>(&magicNumber), sizeof(std::uint32_t));
    if (magicNumber != Map::BLK_MAGIC_WORD) {
        throw Dummy::Core::WrongMagicNumber();
    }
}

} // namespace Core

} // namespace Dummy
