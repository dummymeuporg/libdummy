#pragma once

#include <string>

namespace Dummy {
namespace Local {

class Event {
public:
    Event(const std::string&);
private:
    std::string m_luaCallback;
};

} // namespace Local
} // namespace Dummy
