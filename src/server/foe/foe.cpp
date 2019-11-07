#include <boost/date_time/posix_time/posix_time.hpp>

#include <dummy/core/character.hpp>
#include <dummy/core/map.hpp>
#include <dummy/core/foe.hpp>

#include <dummy/protocol/map_update/living_on.hpp>

#include <dummy/server/foe/foe.hpp>
#include <dummy/server/map.hpp>
#include <dummy/server/map_state.hpp>


namespace Dummy {
namespace Server {
namespace Foe {

Foe::Foe(const Dummy::Core::Foe& foe, boost::asio::io_context& ioContext)
    : m_ioContext(ioContext),
      m_tickTimer(std::make_shared<boost::asio::steady_timer>(m_ioContext)),
      m_luaState(::luaL_newstate())
{
    *static_cast<Foe**>(lua_getextraspace(m_luaState)) = this;
    loadLuaFile(foe.luaFilename());
}

void Foe::start() {
    tick();
}

void Foe::registerLuaCallbacks() {
    lua_register(
        m_luaState,
        "Say",
        &dispatch<&Foe::luaSay>
    );
}

void Foe::loadLuaFileOnStack() {
    auto ret = luaL_loadfile(m_luaState, m_luaFilename.c_str());
    if (0 != ret) {
        std::string errorMessage = lua_tostring(m_luaState, -1);
        std::cerr << "Error: " << errorMessage << std::endl;
        throw LuaLoadFileError();
    }

    // Keep track of the lua file.
    m_luaFileRef = luaL_ref(m_luaState, LUA_REGISTRYINDEX);
}

void Foe::loadLuaFile(const std::string& filename) {
    std::cerr << "File: " << filename << std::endl;

    m_luaFilename = filename;

    luaL_openlibs(m_luaState);
    loadLuaFileOnStack();

    int isNum(0);

    lua_rawgeti(m_luaState, LUA_REGISTRYINDEX, m_luaFileRef);

    // Feed properties.
    lua_pcall(m_luaState, 0, 1, 0);
    if (!lua_istable(m_luaState, -1)) {
        throw LuaNotATable();
    }

    m_luaTableRef = luaL_ref(m_luaState, LUA_REGISTRYINDEX);

    // Push back the table on the stack.
    lua_rawgeti(m_luaState, LUA_REGISTRYINDEX, m_luaTableRef);

    // Read chipset.
    lua_pushstring(m_luaState, "chipset");
    lua_gettable(m_luaState, -2);
    m_chipset = lua_tostring(m_luaState, -1);
    lua_pop(m_luaState, 1); // Get rid of the value

    // Read x
    lua_pushstring(m_luaState, "x");
    lua_gettable(m_luaState, -2);
    m_position.first = static_cast<std::uint16_t>(
        lua_tointegerx(m_luaState, -1, &isNum)
    );
    if (0 == isNum) {
        throw LuaNotAnInteger();
    }
    m_position.first *= 2;
    lua_pop(m_luaState, 1); // Get rid of the value

    // Read y
    lua_pushstring(m_luaState, "y");
    lua_gettable(m_luaState, -2);
    m_position.second = static_cast<std::uint16_t>(
        lua_tointegerx(m_luaState, -1, &isNum)
    );
    if (0 == isNum) {
        throw LuaNotAnInteger();
    }
    m_position.second *= 2;
    lua_pop(m_luaState, 1); // Get rid of the value

    // Read floor
    lua_pushstring(m_luaState, "map_floor");
    lua_gettable(m_luaState, -2);
    m_floor = static_cast<std::uint8_t>(
        lua_tointegerx(m_luaState, -1, &isNum)
    );
    if (0 == isNum) {
        throw LuaNotAnInteger();
    }
    lua_pop(m_luaState, 1); // Get rid of the value

    registerLuaCallbacks();
    setLocalPosition();

}

void Foe::setLocalPosition() {
    m_localPosition.first = m_position.first * 8;
    m_localPosition.second = m_position.second * 8;
}

void Foe::tick() {
    auto self(shared_from_this());
    std::cerr << "Tick!" << std::endl;

    luaTick();

    m_tickTimer->expires_after(std::chrono::milliseconds(333));

    m_tickTimer->async_wait([this, self](const boost::system::error_code&) {
        m_tickTimer = std::make_shared<boost::asio::steady_timer>(m_ioContext);
        tick();
    });
}

void Foe::notifyOn(MapUpdatesVector& mapUpdates) {
    mapUpdates.push_back(
        std::make_unique<Dummy::Protocol::MapUpdate::LivingOn>(
            m_id.value(),
            m_position.first,
            m_position.second,
            m_floor,
            m_chipset,
            Dummy::Core::Character::Direction::DOWN
        )
    );
}

void Foe::notifyPosition(MapUpdatesVector& mapUpdates) {
    mapUpdates.push_back(
        std::make_unique<
            Dummy::Protocol::MapUpdate::CharacterPosition
        >(
            m_id.value(),
            m_position.first,
            m_position.second,
            Dummy::Core::Character::Direction::DOWN // XXX: For now.
        ));
}

void Foe::receiveMessage(std::uint32_t, const std::string& message) {
    // Get the table
    lua_rawgeti(m_luaState, LUA_REGISTRYINDEX, m_luaTableRef);


    //lua_pcall(m_luaState, 0, 1, 0); // Get the module instance.
    lua_getfield(m_luaState, -1, "onMessage");

    lua_pushinteger(m_luaState, m_id.value());
    lua_pushstring(m_luaState, message.c_str());


    auto err = lua_pcall(m_luaState, 2, 0, 0);
    if (0 != err) {
        std::string errorMessage = lua_tostring(m_luaState, -1);
        std::cerr << "Error: " << errorMessage << std::endl;
    }

}

void Foe::luaTick() {
    // Get the table
    lua_rawgeti(m_luaState, LUA_REGISTRYINDEX, m_luaTableRef);

    //lua_pcall(m_luaState, 0, 1, 0);

    lua_getfield(m_luaState, -1, "tick");

    auto err = lua_pcall(m_luaState, 0, 1, 0);
    if (0 != err) {
        std::string errorMessage = lua_tostring(m_luaState, -1);
        std::cerr << "Error: " << errorMessage << std::endl;
    } else {
        auto result = lua_tonumber(m_luaState, -1);
        auto intResult = static_cast<unsigned int>(result);
        auto action = static_cast<FoeAction>(intResult);
        interpretAction(action);
    }
}

void Foe::interpretAction(FoeAction action) {
    switch (action) {
    case FoeAction::moveUp:
    case FoeAction::moveUpRight:
    case FoeAction::moveRight:
    case FoeAction::moveDownRight:
    case FoeAction::moveDown:
    case FoeAction::moveDownLeft:
    case FoeAction::moveLeft:
    case FoeAction::moveUpLeft:
        moveOnMap(action);
        break;
    }
}

std::pair<int, int> Foe::getMovement(FoeAction action) {
    switch (action) {
    case FoeAction::moveUp:
        return {0, -1};
    case FoeAction::moveUpRight:
        return {1, -1};
    case FoeAction::moveRight:
        return {1, 0};
    case FoeAction::moveDownRight:
        return {1, 1};
    case FoeAction::moveDown:
        return {0, 1};
    case FoeAction::moveDownLeft:
        return {-1, 1};
    case FoeAction::moveLeft:
        return {-1, 0};
    case FoeAction::moveUpLeft:
        return {-1, 1};
    }
}

std::pair<std::int16_t, std::int16_t> Foe::computeDistance(
    const std::pair<int, int>& movement
) {
    double divisor =
        movement.first != 0 && movement.second != 0 ? SQRT_2 : 1.0;
    auto velocity = 0.5; // XXX: For now
    std::int16_t xDistance(static_cast<unsigned>(
        ((333.0/8.0) * movement.first * velocity) / divisor
    ));
    std::int16_t yDistance(static_cast<unsigned>(
        ((333.0/8.0) * movement.second * velocity) / divisor
    ));
    return {xDistance, yDistance};
}

void Foe::moveOnMap(FoeAction action) {
    auto movement(getMovement(action));
    auto distance(computeDistance(movement));

    // XXX: For now, do not check collisions...
    m_localPosition.first += distance.first;
    m_localPosition.second += distance.second;

    // Update server coordinates if necessary.
    auto map = m_map.lock();

    std::pair<std::uint16_t, std::uint16_t> newPosition{
        m_localPosition.first / 8,
        m_localPosition.second / 8
    };

    /*
    if (nullptr != map && !map->isBlocking(
                newPosition.first,
                newPosition.second,
                m_floor)
    ) {
    */
        m_position = newPosition;
    //}

}

std::pair<std::uint16_t, std::uint16_t> Foe::position() {
    return m_position;
}

int Foe::luaSay(::lua_State* luaState) {
    std::string message(lua_tostring(luaState, 1));

    boost::asio::post(m_ioContext,
                              [this,
                              map=m_map.lock(),
                              message]()
    {
        if (nullptr != map) {
            map->dispatchMessage(m_id.value(), message);
        }
    });


    return 1;
}

} // namespace Foe
} // namespace Server
} // namespace Dummy
