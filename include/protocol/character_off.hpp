#pragma once

#include <string>
#include "protocol/map_update_manager.hpp"
#include "protocol/map_update.hpp"

namespace Dummy {

namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

class CharacterOff : public MapUpdate {
public:
    CharacterOff(const std::string&);

    virtual std::uint16_t code() override {
        return static_cast<std::uint16_t>(
            MapUpdateManager::Code::CHARACTER_OFF
        );
    }

protected:
    virtual void _streamToPacket(OutgoingPacket&) const override;
    virtual void _streamFromPacket(IncomingPacket&) override;

private:
    std::string m_name;
};

} // namespace Protocol

} // namespace Dummy
