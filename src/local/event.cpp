#include <iostream>

#include "dummy/local/event.hpp"
#include "dummy/local/floor.hpp"

namespace Dummy {
namespace Local {

Event::Event(
    ::lua_State* eventsState,
    const Floor& floor,
    const std::string& luaCallback
) : m_eventsState(eventsState), m_floor(floor), m_luaCallback(luaCallback) {}


void Event::execute() const {
    // Check that the callback is actually defined.
    ::lua_getglobal(m_eventsState, m_luaCallback.c_str());
    if (lua_isfunction(m_eventsState, -1)) {
        if (0 == lua_pcall(m_eventsState, 0, 0, 0)) {
            std::cerr << "Event executed." << std::endl;
        } else {
            std::cerr << "Error lua_pcall." << std::endl;
        }
    } else {
        std::cerr << "Error lua_isfunction." << std::endl;
    }
}

} // namespace Local
} // namespace Dummy
