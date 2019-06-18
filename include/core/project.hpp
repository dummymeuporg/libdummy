#pragma once

#include <exception>
#include <filesystem>
#include <map>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/map.hpp"

namespace fs = std::filesystem;
namespace pt = boost::property_tree;

namespace Dummy
{

namespace Core
{

class ProjectError : public std::exception {

};

class ProjectFileNotFound : public ProjectError {
public:
    virtual const char* what() const noexcept {
        return "project.xml file could not be found";
    }
};

class MapNotFound : public ProjectError {
public:
    virtual const char* what() const noexcept {
        return "the map could not be found";
    }
};

class IncompleteStartingPosition : public ProjectError {
public:
    virtual const char* what() const noexcept {
        return "the starting position is incomplete";
    }
};

class IncorrectStartingPosition : public ProjectError {
public:
    virtual const char* what() const noexcept {
        return "the starting position is incorrect.";
    }
};

class Project
{
public:
    Project(const fs::path&);
    Project(const std::string&);
    virtual ~Project();
    const fs::path& projectPath() const {
        return m_projectPath;
    }

    const std::map<std::string, std::unique_ptr<Map>>& maps() const {
        return m_maps;
    }

    const Map& getMap(const std::string& mapName) const {
        return *m_maps.at(mapName);
    }

    const std::pair<std::uint16_t, std::uint16_t>& startingPosition() const {
        return m_startingPosition;
    }

    const std::string& startingMap() const {
        return m_startingMap;
    }

    void load();
protected:
    virtual void onMapFound(const std::string&);
private:
    void _browseNode(pt::ptree);
    void _setStartingPoint(pt::ptree);

    /* Private attributes */
    fs::path m_projectPath;
    std::map<std::string, std::unique_ptr<Map>> m_maps;
    std::pair<std::uint16_t, std::uint16_t> m_startingPosition;
    std::string m_startingMap;
};


} // namespace Core

} // namespace Dummy
