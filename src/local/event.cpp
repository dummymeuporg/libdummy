#include <dummy/local/event.hpp>

namespace Dummy {
namespace Local {

Event::Event(const std::string& luaCallback) : m_luaCallback(luaCallback) {}

} // namespace Local
} // namespace Dummy
