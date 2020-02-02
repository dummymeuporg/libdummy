#pragma once

#include <string>

extern "C"
{
#include <lualib.h>
}

namespace Dummy {
namespace Local {

class Floor;

class Event
{
public:
    Event(::lua_State*, const Floor&, const std::string&);
    const std::string& luaCallback() const { return m_luaCallback; }
    void execute() const;

private:
    ::lua_State* m_eventsState;
    const Floor& m_floor;
    std::string m_luaCallback;
};

} // namespace Local
} // namespace Dummy
