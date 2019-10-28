#pragma once

#include <dummy/core/map.hpp>
#include <dummy/local/floor.hpp>

namespace Dummy
{
namespace Local
{

class Event;
class EventObserver;
class Floor;
class Project;

using Floors = std::vector<Floor>;
using Events = std::map<std::uint16_t, std::shared_ptr<Event>>;

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

    void setEventObserver(EventObserver*);
protected:
    // XXX: Move this elsewhere?
    int luaOnTouchEvent(::lua_State*) override;
    int luaMessage(::lua_State*) override;
    int luaTeleport(::lua_State*) override;
    int luaAddFoe(::lua_State*) override;


    void loadMapFile(std::ifstream&);
    void readMapFloor(std::ifstream&, std::ifstream&);
    const Project& m_project;
    std::string m_chipset;
    std::string m_music;
    Floors m_floors;
    EventObserver* m_eventObserver;

};

} // namespace Core

} // namespace Dummy
