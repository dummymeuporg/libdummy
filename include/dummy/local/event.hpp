#pragma once

#include <string>

namespace Dummy {
namespace Local {

class Event {
public:
    Event();
private:
    std::string m_luaCallback;
};

} // namespace Local
} // namespace Dummy
