#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include <boost/asio.hpp>

#include <dummy/server/map_observer.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


namespace Dummy {

namespace Core {

class Foe;
} // namespace Core


namespace Server {

namespace Foe {

class Foe : public MapObserver {
public:
    Foe(const Core::Foe&, boost::asio::io_context&);

    const std::string& chipset() const {
        return m_chipset;
    }

    std::uint16_t x() const {
        return m_position.first;
    }

    std::uint16_t y() const {
        return m_position.second;
    }

    std::uint8_t floor() const {
        return m_floor;
    }

    int luaSay(::lua_State*);

    void notifyOn(MapUpdatesVector&) override;
    void notifyPosition(MapUpdatesVector&) override;
    void receiveMessage(std::uint32_t, const std::string&) override;
    std::pair<std::uint16_t, std::uint16_t> position() override;
    void start();
    void tick();

private:
    void loadLuaFile(const std::string&);
    void registerLuaCallbacks();
    void loadLuaFileOnStack();

    boost::asio::io_context& m_ioContext;
    std::shared_ptr<boost::asio::steady_timer> m_tickTimer;

    std::string m_luaFilename;
    ::lua_State* m_luaState;
    int m_luaFileRef;
    std::string m_chipset;
    std::pair<std::uint16_t, std::uint16_t> m_position;
    std::uint8_t m_floor;
};

typedef int (Foe::*mem_func)(::lua_State* L);

template <mem_func func>
int dispatch(::lua_State * L) {
    Foe* ptr = *static_cast<Foe**>(lua_getextraspace(L));
    return ((*ptr).*func)(L);
}

} // namespace Foe
} // namespace Server
} // namespace Dummy
