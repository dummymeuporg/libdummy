#pragma once

#include <exception>
#include <filesystem>
#include <map>
#include <memory>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "dummy/core/map.hpp"

namespace fs = std::filesystem;
namespace pt = boost::property_tree;

namespace Dummy {
namespace Local {

class Map;

class ProjectError : public std::exception
{};

class ProjectFileNotFound : public ProjectError
{
public:
    virtual const char* what() const noexcept
    {
        return "project.xml file could not be found";
    }
};

class MapNotFound : public ProjectError
{
public:
    virtual const char* what() const noexcept
    {
        return "the map could not be found";
    }
};

class IncompleteStartingPosition : public ProjectError
{
public:
    virtual const char* what() const noexcept
    {
        return "the starting position is incomplete";
    }
};

class IncorrectStartingPosition : public ProjectError
{
public:
    virtual const char* what() const noexcept
    {
        return "the starting position is incorrect.";
    }
};

class Project
{
public:
    Project(const fs::path&);
    Project(const std::string&);
    virtual ~Project();
    const fs::path& projectPath() const { return m_projectPath; }

private:
    /* Private attributes */
    fs::path m_projectPath;
};


} // namespace Local
} // namespace Dummy
