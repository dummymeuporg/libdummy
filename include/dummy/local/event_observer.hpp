#pragma once

#include <string>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace Dummy {
namespace Local {

class EventObserver {
public:
    virtual void onMessage(const std::string&) = 0;
    virtual void onTeleport(
        const std::string&,
        std::uint16_t,
        std::uint16_t,
        std::uint8_t
    ) = 0;
};

} // namespace Local
} // namespace Dummy
