#include <iostream>
#include <queue>

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
    // Identify starting map.
    _loadProjectFile();
}

void Project::_loadProjectFile() {

    fs::path projectXMLPath(m_projectPath / "project.xml");

    if (!fs::exists(projectXMLPath)) {
        throw ProjectFileNotFound();
    }

    pt::ptree tree;

    std::cerr << "Load project.xml file." << std::endl;
    pt::read_xml(projectXMLPath.string(), tree);

    _browseNode(tree.get_child("project.maps"));
}

void Project::_browseNode(pt::ptree node) {
    for (const auto& it: node) {
        if (it.first == "map")
        {
            for (const auto& child: it.second.get_child("<xmlattr>"))
            {
                if (child.first == "name") {
                    m_maps[child.second.data()] = nullptr;
                }
            }
            if (it.second.count("map") > 0) {
                _browseNode(it.second);
            }
        }
    }
}
    

} // namespace Core

} // namespace Dummy
