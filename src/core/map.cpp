#pragma once

#include "core/map.hpp"

namespace Dummy
{

namespace Core
{

Map::Map(std::uint16_t width, std::uint16_t height)
    : m_width(width), m_height(height),
      m_blocking(width * height * sizeof(std::uint8_t))
{
}

void Map::_loadFromStream(std::fstream& fs) {
    std::uint32_t magicNumber;
    std::uint32_t version;

    fs.read(reinterpret_cast<char*>(&magicNumber), sizeof(std::uint32_t));
    if (magicNumber != MAGIC_WORD)
    {
        throw WrongMagicNumber();
    }

    fs.read(reinterpret_cast<char*>(&version), sizeof(std::uint32_t));

}

std::fstream& operator>>(std::fstream& fs, Map& map) {
    map._loadFromStream(fs);
    return fs;
}

} // namespace Core

} // namespace Dummy
