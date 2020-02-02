#pragma once

#include <exception>
#include <filesystem>
#include <optional>
#include <set>

#include <boost/property_tree/ptree.hpp>

#include "dummy/core/starting_point.hpp"

namespace fs = std::filesystem;
namespace pt = boost::property_tree;

namespace Dummy {
namespace Core {

class Project
{
public:
    Project(const fs::path&);
    const fs::path& projectPath() const { return m_projectPath; }

    const StartingPoint& startingPoint() const { return m_startingPoint; }

    void load();

    const std::set<std::string>& maps() const { return m_maps; }

protected:
    virtual void onMapFound(const std::string&);
    virtual bool mapExists(const std::string&);

protected:
    void parseMapsList(pt::ptree);
    void parseStartingPoint(pt::ptree);

    /* Private attributes */
    fs::path m_projectPath;
    StartingPoint m_startingPoint {"", {0, 0}, 0};
    std::set<std::string> m_maps;
};

//////////////////////////////////////////////////////////////////

class ProjectFileError : public std::exception
{
public:
    ProjectFileError(const char* const msg)
        : std::exception(msg)
    {}
};

} // namespace Core
} // namespace Dummy
