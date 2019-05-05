#pragma once

#include <exception>
#include <map>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace fs = boost::filesystem;
namespace pt = boost::property_tree;

namespace Dummy
{

namespace Core
{

class ProjectError : public std::exception {

};

class ProjectFileNotFound : public ProjectError {
    virtual const char* what() const noexcept {
        return "project.xml file could not be found";
    }
};

class Project
{
public:
    Project(const fs::path&);

    const std::map<std::string, std::unique_ptr<void*>>& maps() const {
        return m_maps;
    }
private:
    void _loadProjectFile();
    void _browseNode(pt::ptree);

    /* Private attributes */
    fs::path m_projectPath;
    std::map<std::string, std::unique_ptr<void*>> m_maps;
};


} // namespace Core

} // namespace Dummy
