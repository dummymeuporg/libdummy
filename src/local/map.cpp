#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

#include "dummy/core/errors.hpp"
#include "dummy/core/graphic_layer.hpp"

#include "dummy/local/event.hpp"
#include "dummy/local/event_observer.hpp"
#include "dummy/local/map.hpp"
#include "dummy/local/project.hpp"

namespace fs = std::filesystem;

namespace Dummy
{

namespace Local
{

Map::Map(const Project& project, const std::string& name)
    : Dummy::Core::Map(name), m_project(project), m_eventObserver(nullptr)
{
    std::cerr << "Local map constructor" << std::endl;
}

void Map::load() {
    fs::path basePath(m_project.projectPath() / "maps");
    std::string mapFile(m_name + ".map");
    std::string blkFile(m_name + ".blk");
    std::string luaFile(m_name + ".lua");

    std::ifstream ifsMapFile(basePath / mapFile, std::ios::binary);
    if (!ifsMapFile.is_open()) {
        throw Dummy::Core::MapFileNotFound();
    }

    std::ifstream ifsBlkFile(basePath / blkFile, std::ios::binary);
    if (!ifsBlkFile.is_open()) {
        throw Dummy::Core::BlkFileNotFound();
    }
    loadMapFile(ifsMapFile);
    readBlkFile(ifsBlkFile);

    for (int i = 0; i < m_floorsCount; ++i) {
        readMapFloor(ifsMapFile, ifsBlkFile);
    }

    loadLuaFile((basePath / luaFile).string());
}

void Map::loadMapFile(std::ifstream& ifs) {
    Dummy::Core::Map::loadBaseInfo(ifs);
    std::cerr << "Map::loadMapFile" << std::endl;
    std::uint32_t strSize;

    /* Read chipset. */
    ifs.read(reinterpret_cast<char*>(&strSize), sizeof(std::uint32_t));
    if (0 != strSize) {
        m_chipset.resize(strSize);
        ifs.read(m_chipset.data(), strSize);
    } else {
        m_chipset = ""; // XXX should not happen. Throw exception?
    }

    std::cerr << "Chipset: " << m_chipset << std::endl;

    /* Read music */
    ifs.read(reinterpret_cast<char*>(&strSize), sizeof(std::uint32_t));
    if (0 != strSize) {
        m_music.resize(strSize);
        ifs.read(m_music.data(), strSize);
    } else {
        m_music = "";
    }
}

void Map::readMapFloor(
    std::ifstream& ifsMapFile,
    std::ifstream& ifsBlkFile)
{
    Floor floor(*this);
    std::size_t elements = m_width * m_height;
    std::uint8_t layersCount;

    // Read layers count
    ifsMapFile.read(
        reinterpret_cast<char*>(&layersCount),
        sizeof(std::uint8_t)
    );

    for(std::uint8_t i = 0; i < layersCount; i++) {
        // Read the layer position
        std::int8_t position;
        ifsMapFile.read(
            reinterpret_cast<char*>(&position), sizeof(std::uint8_t)
        );
        Dummy::Core::GraphicLayer graphicLayer(m_width, m_height);
        // read the whole layer
        ifsMapFile.read(
            reinterpret_cast<char*>(graphicLayer.data()),
            static_cast<std::streamsize>(
                elements * sizeof(std::pair<std::int8_t, std::int8_t>)
            )
        );
        floor.addGraphicLayer(position, std::move(graphicLayer));
    }
    // Read the blocking layer
    Dummy::Core::BlockingLayer&& blockingLayer = loadBlockingLayer(ifsBlkFile);
    floor.setBlockingLayer(std::move(blockingLayer));

    // Create the floor.
    m_floors.push_back(std::move(floor));
}

int Map::luaOnKeypressEvent(::lua_State* luaState) {
    int isNum;
    std::uint16_t x, y;
    std::uint8_t floor;
    x = static_cast<std::uint16_t>(lua_tointegerx(luaState, 1, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    y = static_cast<std::uint16_t>(lua_tointegerx(luaState, 2, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    floor = static_cast<std::uint8_t>(lua_tointegerx(luaState, 3, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    std::string luaCallback = lua_tostring(luaState, 4);
    auto index = y * m_width + x;
    auto& currentFloor(m_floors[floor]);
    currentFloor.keypressEvents().emplace(index, std::make_shared<Event>(
        m_eventsState,
        *this,
        luaCallback
    ));
    return 1;
}

int Map::luaOnTouchEvent(::lua_State* luaState) {
    int isNum;
    std::uint16_t x, y;
    std::uint8_t floor;
    x = static_cast<std::uint16_t>(lua_tointegerx(luaState, 1, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    y = static_cast<std::uint16_t>(lua_tointegerx(luaState, 2, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    floor = static_cast<std::uint8_t>(lua_tointegerx(luaState, 3, &isNum));
    if (0 == isNum) {
        // XXX: Throw an exception
    }

    std::string luaCallback = lua_tostring(luaState, 4);
    auto index = y * m_width + x;
    auto& currentFloor(m_floors[floor]);
    currentFloor.touchEvents().emplace(index, std::make_shared<Event>(
        m_eventsState,
        *this,
        luaCallback
    ));
    return 1;
}

int Map::luaMessage(::lua_State* luaState) {
    if (m_eventObserver != nullptr) {
        std::string message = lua_tostring(luaState, 1);
        m_eventObserver->onMessage(message);
        return 1;
    }
    return 0;
}

int Map::luaTeleport(::lua_State* luaState) {
    if (m_eventObserver != nullptr) {
        std::uint16_t x, y;
        std::uint8_t floor;
        int isNum;
        std::string mapDestination = lua_tostring(luaState, 1);

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

        m_eventObserver->onTeleport(mapDestination, x, y, floor);
        return 1;
    }
    return 0;
}

int Map::luaAddFoe(::lua_State* luaState) {
    std::string luaFilename = lua_tostring(luaState, 1);
    fs::path fullpath(m_project.projectPath() / "foes");
    fullpath /= luaFilename;

    m_foes.push_back(Dummy::Core::Foe(fullpath.string()));

    return 1;
}

void Map::setEventObserver(EventObserver* eventObserver) {
    m_eventObserver = eventObserver;
}


} // namespace Core
} // namespace Dummy
