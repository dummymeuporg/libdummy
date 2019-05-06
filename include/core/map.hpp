#pragma once

#include <cstdint>
#include <exception>
#include <fstream>
#include <vector>

namespace Dummy
{

namespace Core
{

class MapError : public std::exceptions {

};

class WrongMagicNumber : public MapError {
public:
    virtual const char* what() const noexcept {
        return "the magic number is invalid.";
    }
};

class Map {
public:
    const std::uint32_t MAGIC_WORD = 0xF000BABA;
    Map(std::uint16_t, std::uint16_t);
    friend std::fstream& operator>>(std::fstream&, Map&);
private:
    void _loadFromStream(std::fstream&);
    std::uint16_t m_width, m_height;
    std::vector<std::uint8_t> m_blocking;
};

