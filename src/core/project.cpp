#include <iostream>
#include <queue>
#include <sstream>

#include "core/project.hpp"

namespace fs = std::filesystem;
namespace pt = boost::property_tree;

namespace Dummy
{

namespace Core
{

Project::Project(const fs::path& projectPath) : m_projectPath(projectPath)
{
    // Load project.xml
    // Identify starting map.
}

Project::Project(const std::string& projectPath) :
    m_projectPath(fs::path(projectPath))
{}

Project::~Project() {}

void Project::load() {

    fs::path projectXMLPath(m_projectPath / "project.xml");

    if (!fs::exists(projectXMLPath)) {
        throw ProjectFileNotFound();
    }

    pt::ptree tree;

    std::cerr << "Load project.xml file." << std::endl;
    pt::read_xml(projectXMLPath.string(), tree);

    _browseNode(tree.get_child("project.maps"));
    _setStartingPoint(tree.get_child("project.starting_point"));
}

void Project::_setStartingPoint(pt::ptree node) {
    std::string x, y, map, floorString;
    std::pair<std::uint16_t, std::uint16_t> position;
    std::uint16_t floor;

    for(const auto& child: node.get_child("<xmlattr>")) {
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
        throw IncompleteStartingPosition();
    }
    std::istringstream iss(x);
    iss >> position.first;

    if (iss.bad()) {
        throw IncorrectStartingPosition();
    }
    std::cerr << "x = " << position.first << std::endl;

    iss.str(y);
    iss.seekg(0);
    iss >> position.second;

    if (iss.bad()) {
        throw IncorrectStartingPosition();
    }
    std::cerr << "y = " << position.second << std::endl;

    if (!mapExists(map)) {
        throw MapNotFound();
    }

    iss.str(floorString);
    iss.seekg(0);
    iss >> floor;

    // From here, everything is correct.
    m_startingPoint = std::make_optional<StartingPoint>(map, position, floor);

}

void Project::_browseNode(pt::ptree node) {
    for (const auto& it: node) {
        if (it.first == "map")
        {
            for (const auto& child: it.second.get_child("<xmlattr>"))
            {
                if (child.first == "name") {
                    onMapFound(child.second.data());
                }
            }
            if (it.second.count("map") > 0) {
                _browseNode(it.second);
            }
        }
    }
}

void Project::onMapFound(const std::string&) {
    // XXX: Set it as a pure virtual function later.
}

bool Project::mapExists(const std::string&) {
    // XXX: Set it as a pure virtual function later.
    return false;
}

} // namespace Core

} // namespace Dummy
