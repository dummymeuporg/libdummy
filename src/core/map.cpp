#include <iostream>
#include <fstream>

#include <dummy/core/blocking_layer.hpp>
#include <dummy/core/map.hpp>
#include <dummy/core/project.hpp>


extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace fs = std::filesystem;

namespace Dummy
{

namespace Core
{

Map::Map(const std::string& name) : m_name(name), m_width(1), m_height(1),
    m_floorsCount(0), m_eventsState(::luaL_newstate())
{
    // Pass the Map instance to the lua extraspace
    *static_cast<Map**>(lua_getextraspace(m_eventsState)) = this;
}

Map::~Map() {
    if (nullptr != m_eventsState) {
        ::lua_close(m_eventsState);
        m_eventsState = nullptr;
    }
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

    // read the number of floors
    ifs.read(reinterpret_cast<char*>(&m_floorsCount), sizeof(std::uint8_t));
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

void Map::loadLuaFile(const std::string& luaFile) {
    std::cerr << "File: " << luaFile << std::endl;

    lua_register(
        m_eventsState,
        "OnTouchEvent",
        &dispatch<&Map::luaOnTouchEvent>
    );

    lua_register(
        m_eventsState,
        "Message",
        &dispatch<&Map::luaMessage>
    );

    lua_register(
        m_eventsState,
        "Teleport",
        &dispatch<&Map::luaTeleport>
    );

    lua_register(
        m_eventsState,
        "AddFoe",
        &dispatch<&Map::luaAddFoe>
    );

    lua_register(
        m_eventsState,
        "AddLuaFoe",
        &dispatch<&Map::luaAddLuaFoe>
    );

    int ret = luaL_dofile(m_eventsState, luaFile.c_str());
    if (ret != 0) {
        throw Dummy::Core::LuaFileNotFound();
    }
}

int Map::luaAddFoe(::lua_State* luaState) {
    std::uint16_t x, y;
    std::uint8_t floor;
    int isNum;
    std::string chipset = lua_tostring(luaState, 1);

    x = static_cast<std::uint16_t>(lua_tointegerx(luaState, 2, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    y = static_cast<std::uint16_t>(lua_tointegerx(luaState, 3, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    floor = static_cast<std::uint8_t>(lua_tointegerx(luaState, 4, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    m_foes.push_back(Foe(chipset, x, y, floor));

    return 1;
}

} // namespace Core

} // namespace Dummy
