#include <dummy/local/event.hpp>
#include <dummy/local/floor.hpp>

namespace Dummy {
namespace Local {

Event::Event(const Floor& floor, const std::string& luaCallback)
    : m_floor(floor), m_luaCallback(luaCallback) {}

} // namespace Local
} // namespace Dummy
