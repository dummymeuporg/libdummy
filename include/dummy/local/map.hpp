#pragma once

#include <dummy/core/map.hpp>
#include <dummy/local/level.hpp>

namespace Dummy
{
namespace Local
{

class Level;
class Project;

using Levels = std::vector<Level>;

class Map : public Dummy::Core::Map {
public:
    Map(const Project&, const std::string&);


    void load() override;

    const std::string& chipset() const {
        return m_chipset;
    }

    const std::string& music() const {
        return m_music;
    }

    const Levels& levels() const {
        return m_levels;
    }
protected:
    void loadMapFile(std::ifstream&);
    void readMapLevel(std::ifstream&, std::ifstream&);

    const Project& m_project;

    std::string m_chipset;
    std::string m_music;
    Levels m_levels;
};

} // namespace Core

} // namespace Dummy
