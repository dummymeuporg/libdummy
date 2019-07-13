#include <iostream>
#include "remote/map.hpp"
#include "server/project.hpp"

namespace Dummy {
namespace Server {

Project::Project(const std::string& projectPath)
    : Core::Project(projectPath) {}

void Project::onMapFound(const std::string& mapName) {
    // XXX Instantiate a Remote Map.
    std::cerr << "Load remote map " << mapName << std::endl;
    m_maps[mapName] = std::make_unique<Dummy::Remote::Map>(*this, mapName);
    m_maps[mapName]->load();

}

bool Project::mapExists(const std::string& mapName) {
    return m_maps.find(mapName) != std::end(m_maps);
}

} // namespace Server
} // namespace Dummy
