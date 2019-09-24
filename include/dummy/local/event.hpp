#pragma once

#include <string>

namespace Dummy {
namespace Local {

class Floor;

class Event {
public:
    Event(const Floor&, const std::string&);
    const std::string& luaCallback() const {
        return m_luaCallback;
    }
private:
    const Floor& m_floor;
    std::string m_luaCallback;
};

} // namespace Local
} // namespace Dummy
