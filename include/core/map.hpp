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

using BlockingLayer = std::vector<std::uint8_t>;
using BlockingLevels = std::vector<BlockingLayer>;

class Map {
public:
    static const std::uint32_t MAP_MAGIC_WORD = 0xF000BABA;
    static const std::uint32_t BLK_MAGIC_WORD = 0xDEADDAAD;
    static const std::uint16_t VERSION = 1;

    Map(const Project&, const std::string&);
    void load();

    friend std::fstream& operator>>(std::fstream&, Map&);

    const std::string& name() const {
        return m_name;
    }

    std::uint16_t width() const {
        return m_width;
    }

    std::uint16_t height() const {
        return m_height;
    }

    bool isBlocking(std::uint16_t x, std::uint16_t y) const;

    BlockingLayer& blockingLayer() {
        return m_blockingLevels[0];
    }

    const BlockingLayer& blockingLayer() const {
        return m_blockingLevels.at(0);
    }

    const BlockingLevels& blockingLevels() const {
        return m_blockingLevels;
    }

    const BlockingLayer& blockingLevel(unsigned long long index) {
        return m_blockingLevels.at(index);
    }

    void setDimensions(std::uint16_t, std::uint16_t);
    void addBlockingLevel(BlockingLayer&&);

protected:
    void _loadBlkFile(std::string);
    virtual void _loadMapFile(std::ifstream&);

    const Project& m_project;
    std::string m_name;
    std::uint16_t m_width, m_height;
    BlockingLayer m_blockingLayer; // XXX: to remove
    BlockingLevels m_blockingLevels;
private:
    void _internalLoadMapFile(std::string);
};

} // namespace Core

} // namespace Dummy
