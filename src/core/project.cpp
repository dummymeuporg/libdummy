#include "dummy/core/project.hpp"

#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace fs = std::filesystem;
namespace pt = boost::property_tree;

namespace Dummy {
namespace Core {

Project::Project(const fs::path& projectPath)
    : m_projectPath(projectPath)
{
    load();
}

void Project::load()
{
    // Load project.xml
    // Identify starting map.

    fs::path projectXMLPath(m_projectPath / "project.xml");
    if (! fs::exists(projectXMLPath)) {
        throw ProjectFileError("Project.xml file could not be found.");
    }

    try {
        pt::ptree tree;
        pt::read_xml(projectXMLPath.string(), tree);
        parseMapsList(tree.get_child("project.maps"));
        parseStartingPoint(tree.get_child("project.starting_point"));

    } catch (pt::xml_parser_error) {
        throw ProjectFileError("Project.xml file could not be parsed.");
    } catch (pt::ptree_bad_path) {
        throw ProjectFileError("Project.xml file has missing data.");
    }
}

void Project::parseStartingPoint(pt::ptree node)
{
    std::string x, y, map, floorString;
    tilecoords position;
    uint8_t floor;

    for (const auto& child : node.get_child("<xmlattr>")) {
        if (child.first == "x") {
            x = child.second.data();
        } else if (child.first == "y") {
            y = child.second.data();
        } else if (child.first == "map") {
            map = child.second.data();
        } else if (child.first == "floor") {
            floorString = child.second.data();
        }
    }

    if (x == "" || y == "" || map == "" || floorString == "") {
        throw ProjectFileError("The starting position is incomplete.");
    }

    try {
        position.first  = boost::lexical_cast<uint16_t>(x);
        position.second = boost::lexical_cast<uint16_t>(y);
        floor           = boost::lexical_cast<uint8_t>(floorString);
    } catch (boost::bad_lexical_cast) {
        throw ProjectFileError("The starting position is incorrect.");
    }

    if (! mapExists(map)) {
        throw ProjectFileError("The starting point's map could not be found.");
    }

    // From here, everything is correct.
    m_startingPoint = StartingPoint(map, position, floor);
}

void Project::parseMapsList(pt::ptree node)
{
    for (const auto& it : node) {
        if (it.first == "map") {
            for (const auto& child : it.second.get_child("<xmlattr>")) {
                if (child.first == "name") {
                    m_maps.insert(child.second.data());
                    onMapFound(child.second.data());
                }
            }
            if (it.second.count("map") > 0) {
                parseMapsList(it.second);
            }
        }
    }
}

void Project::onMapFound(const std::string&)
{
    // XXX: Set it as a pure virtual function later.
}

bool Project::mapExists(const std::string&)
{
    // XXX: Set it as a pure virtual function later.
    return false;
}

} // namespace Core
} // namespace Dummy
