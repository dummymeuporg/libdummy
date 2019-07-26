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

    for (int i = 0; i < m_levelsCount; ++i) {
        m_floors.push_back(std::move(loadBlockingLayer(ifsBlkFile)));
    }

}

} // namespace Remote
} // namespace Dummy
