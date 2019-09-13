#pragma once

#include <cstdint>
#include <exception>
#include <fstream>
#include <vector>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

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

class LuaFileNotFound : public MapError {
public:
    virtual const char* what() const noexcept {
        return "the lua file could not be found";
    }
};

class Project;

class BlockingLayer;
using BlockingFloors = std::vector<BlockingLayer>;



class Map {
public:
    static const std::uint32_t MAP_MAGIC_WORD = 0xF000BABA;
    static const std::uint32_t BLK_MAGIC_WORD = 0xDEADDAAD;
    static const std::uint16_t VERSION = 1;

    Map(const std::string&);
    virtual ~Map();

    const std::string& name() const {
        return m_name;
    }

    std::uint16_t width() const {
        return m_width;
    }

    std::uint16_t height() const {
        return m_height;
    }

    virtual void load() = 0;

protected:
    void loadBaseInfo(std::ifstream&);
    BlockingLayer loadBlockingLayer(std::ifstream&);
    void readBlkFile(std::ifstream& ifs);
    void loadLuaFile(const std::string&);

    // XXX: export this elsewhere?
    virtual int luaOnTouchEvent(::lua_State*) = 0;

protected:
    std::string m_name;
    std::uint16_t m_width, m_height;
    std::uint8_t m_floorsCount;
    ::lua_State* m_eventsState;
    void internalLoadMapFile(std::string);
};

typedef int (Map::*mem_func)(::lua_State* L);

template <mem_func func>
int dispatch(::lua_State * L) {
    Map* ptr = *static_cast<Map**>(lua_getextraspace(L));
    return ((*ptr).*func)(L);
}

} // namespace Core

} // namespace Dummy
