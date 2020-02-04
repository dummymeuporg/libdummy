#include "dummy/core/map.hpp"

#include <iostream>

#include "dummy/core/layer.hpp"

namespace fs = std::filesystem;

namespace Dummy {
namespace Core {

Map::Map(const std::string& name)
    : m_name(name)
    , m_width(1)
    , m_height(1)
    , m_floorsCount(0)
    , m_eventsState(::luaL_newstate())
{
    // Pass the Map instance to the lua extraspace
    *static_cast<Map**>(lua_getextraspace(m_eventsState)) = this;
}

Map::~Map()
{
    if (nullptr != m_eventsState) {
        ::lua_close(m_eventsState);
        m_eventsState = nullptr;
    }
}

void Map::loadBaseInfo(std::ifstream& ifs)
{
    uint32_t magicNumber;
    uint16_t version;
    ifs.read(reinterpret_cast<char*>(&magicNumber), sizeof(uint32_t));
    if (magicNumber != Map::MAP_MAGIC_WORD) {
        throw WrongMagicNumber();
    }

    // XXX what to do with version?
    ifs.read(reinterpret_cast<char*>(&version), sizeof(uint16_t));

    // read dimensions
    ifs.read(reinterpret_cast<char*>(&m_width), sizeof(uint16_t));
    ifs.read(reinterpret_cast<char*>(&m_height), sizeof(uint16_t));

    // read the number of floors
    ifs.read(reinterpret_cast<char*>(&m_floorsCount), sizeof(uint8_t));
}

BlockingLayer Map::loadBlockingLayer(std::ifstream& ifs)
{
    BlockingLayer layer(m_width * 2, m_height * 2, false);
    layer.fillWithRawData(ifs);
    return layer;
}

void Map::readBlkFile(std::ifstream& ifs)
{
    uint32_t magicNumber;

    ifs.read(reinterpret_cast<char*>(&magicNumber), sizeof(uint32_t));
    if (magicNumber != Map::BLK_MAGIC_WORD) {
        throw Dummy::Core::WrongMagicNumber();
    }
}

void Map::loadLuaFile(const std::string& luaFile)
{
    std::cerr << "File: " << luaFile << std::endl;

    lua_register(m_eventsState, "OnTouchEvent",
                 &dispatch<&Map::luaOnTouchEvent>);

    lua_register(m_eventsState, "OnKeypressEvent",
                 &dispatch<&Map::luaOnKeypressEvent>);

    lua_register(m_eventsState, "Message", &dispatch<&Map::luaMessage>);

    lua_register(m_eventsState, "Teleport", &dispatch<&Map::luaTeleport>);

    lua_register(m_eventsState, "AddFoe", &dispatch<&Map::luaAddFoe>);

    int ret = luaL_dofile(m_eventsState, luaFile.c_str());
    if (ret != 0) {
        std::string errorMessage(lua_tostring(m_eventsState, -1));
        std::cerr << errorMessage << std::endl;
        throw Dummy::Core::LuaLoadFileError(errorMessage);
    }
}

} // namespace Core
} // namespace Dummy
