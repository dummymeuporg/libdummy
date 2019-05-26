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
    friend std::fstream& operator>>(std::fstream&, Map&);
protected:
    virtual void _internalLoadMapFile(std::string);
    void _loadBlkFile(std::string);

    const Project& m_project;
    std::string m_name;
    std::uint16_t m_width, m_height;
    std::vector<std::uint8_t> m_blocking;
private:
    virtual void _loadMapFile(std::ifstream&);
};

} // namespace Core

} // namespace Dummy
