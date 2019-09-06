#pragma once

#include <dummy/core/map.hpp>
#include <dummy/local/floor.hpp>

namespace Dummy
{
namespace Local
{

class Floor;
class Project;

using Floors = std::vector<Floor>;

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

    const Floors& floors() const {
        return m_floors;
    }
protected:
    void loadMapFile(std::ifstream&);
    void readMapFloor(std::ifstream&, std::ifstream&);
    const Project& m_project;

    std::string m_chipset;
    std::string m_music;
    Floors m_floors;

};

} // namespace Core

} // namespace Dummy
