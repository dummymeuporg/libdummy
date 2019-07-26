#include <iostream>
#include <queue>
#include <sstream>

#include <dummy/local/project.hpp>

namespace fs = std::filesystem;
namespace pt = boost::property_tree;

namespace Dummy
{

namespace Local
{

Project::Project(const fs::path& projectPath) : m_projectPath(projectPath)
{}

Project::Project(const std::string& projectPath) :
    m_projectPath(fs::path(projectPath))
{}

Project::~Project() {}

} // namespace Local

} // namespace Dummy
