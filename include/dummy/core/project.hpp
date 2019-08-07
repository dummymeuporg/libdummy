#pragma once

#include <exception>
#include <filesystem>
#include <map>
#include <memory>
#include <optional>
#include <set>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <dummy/core/map.hpp>
#include <dummy/core/starting_point.hpp>

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
    const char* what() const noexcept override {
        return "project.xml file could not be found";
    }
};

class MapNotFound : public ProjectError {
public:
    const char* what() const noexcept override {
        return "the map could not be found";
    }
};

class IncompleteStartingPosition : public ProjectError {
public:
    const char* what() const noexcept override {
        return "the starting position is incomplete";
    }
};

class IncorrectStartingPosition : public ProjectError {
public:
    const char* what() const noexcept override {
        return "the starting position is incorrect.";
    }
};

class StartingPositionNotSet : public ProjectError {
public:
    const char* what() const noexcept override {
        return "the starting position is not set.";
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

    const StartingPoint& startingPoint() const {
        if (!m_startingPoint.has_value()) {
            throw StartingPositionNotSet();
        }
        return m_startingPoint.value();
    }

    void load();

    const std::set<std::string>& maps() const {
        return m_maps;
    }

protected:
    virtual void onMapFound(const std::string&);
    virtual bool mapExists(const std::string&);
protected:
    void _browseNode(pt::ptree);
    void _setStartingPoint(pt::ptree);

    /* Private attributes */
    fs::path m_projectPath;
    std::optional<StartingPoint> m_startingPoint;
    std::set<std::string> m_maps;
};


} // namespace Core

} // namespace Dummy
