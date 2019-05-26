#include <fstream>
#include <iostream>

#include <boost/filesystem.hpp>

#include "core/graphic_map.hpp"
#include "core/project.hpp"

namespace fs = boost::filesystem;

namespace Dummy
{

namespace Core
{

GraphicMap::GraphicMap(const Project& project, const std::string& name)
    : Map(project, name)
{
} // namespace Core

} // namespace Dummy
