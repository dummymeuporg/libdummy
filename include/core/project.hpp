#pragma once

#include <exceptions>

#include <boost/filesystem.hpp>

namespace Dummy
{

namespace Core
{

class ProjectError : public std::exception {

};

class ProjectFileNotFoundError : public ProjectError {
    virtual const char* what() const noexcept {
        return "project.xml file could not be found";
    }

class Project
{
public:
    Project(const fs::path&);
private:
    void _loadProject();

    /* Private attributes */
    fs::path m_projectPath;
};


} // namespace Core

} // namespace Dummy