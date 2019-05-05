#include "core/project.hpp"

namespace fs = boost::filesystem;
namespace pt = boost::property_tree;

namespace Dummy
{

namespace Core
{

Project::Project(const fs::path& projectPath) : m_projectPath(projectPath)
{
    // Load project.xml
    // Load maps
    // Identify starting map.
}

void Project::_loadProject()
{

}

} // namespace Core

} // namespace Dummy
