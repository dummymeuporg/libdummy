#include "server/project.cpp"

namespace Dummy {
namespace Server {

Project::Project(const std::string& projectPath) {}

void Project::onMapFound(std::string& mapName) {

}

bool Project::mapExists(const std::string& mapName) {
    return false;
}

} // namespace Server
} // namespace Dummy
