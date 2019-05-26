#pragma once

#include <cstdint>
#include <exception>
#include <fstream>
#include <vector>

namespace Dummy
{

namespace Core
{

class MapError : public std::exception {

};

class WrongMagicNumber : public MapError {
public:
    virtual const char* what() const noexcept {
        return "the magic number is invalid";
    }
};

class MapFileNotFound : public MapError {
public:
    virtual const char* what() const noexcept {
        return "the map file could not be found";
    }
};

class BlkFileNotFound : public MapError {
public:
    virtual const char* what() const noexcept {
        return "the blk file could not be found";
    }
};

class Project;

class Map {
public:
    static const std::uint32_t MAP_MAGIC_WORD = 0xF000BABA;
    static const std::uint32_t BLK_MAGIC_WORD = 0xDEADDAAD;
    static const std::uint16_t VERSION = 1;

    Map(const Project&, const std::string&);
    void load();

    friend std::fstream& operator>>(std::fstream&, Map&);

    std::uint16_t width() const {
        return m_width;
    }

    std::uint16_t height() const {
        return m_height;
    }

    bool isBlocking(std::uint16_t x, std::uint16_t y);
protected:
    void _loadBlkFile(std::string);
    virtual void _loadMapFile(std::ifstream&);

    const Project& m_project;
    std::string m_name;
    std::uint16_t m_width, m_height;
    std::vector<std::uint8_t> m_blocking;
private:
    void _internalLoadMapFile(std::string);
};

} // namespace Core

} // namespace Dummy
