#pragma once

#include <string>

namespace Dummy {
namespace Local {

class EventObserver
{
public:
    virtual void onMessage(const std::string&) = 0;
    virtual void onTeleport(const std::string&, uint16_t, uint16_t,
                            uint8_t)      = 0;
};

} // namespace Local
} // namespace Dummy
