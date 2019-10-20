#include <filesystem>

#include <dummy/server/project.hpp>
#include <dummy/remote/map.hpp>

namespace fs = std::filesystem;

namespace Dummy {
namespace Remote {

Map::Map(const Dummy::Server::Project& project, const std::string& name) :
    Core::Map(name), m_project(project)
{}

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

    Dummy::Core::Map::loadBaseInfo(ifsMapFile);
    readBlkFile(ifsBlkFile);

    for (int i = 0; i < m_floorsCount; ++i) {
        m_floors.push_back(loadBlockingLayer(ifsBlkFile));
    }

    loadLuaFile((basePath / luaFile).string());

}

int Map::luaOnTouchEvent(::lua_State*) {
    // XXX: What do we do?
    return 1;
}

int Map::luaMessage(::lua_State*) {
    // XXX: What do we do?
    return 1;
}

int Map::luaTeleport(::lua_State*) {
    // XXX: What do we do?
    return 1;
}

} // namespace Remote
} // namespace Dummy
