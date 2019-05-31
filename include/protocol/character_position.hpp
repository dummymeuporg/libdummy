#pragma once

#include <cstdint>
#include <string>
#include "protocol/map_update_manager.hpp"
#include "protocol/map_update.hpp"
#include "core/character.hpp"

namespace Dummy {

namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

class CharacterPosition : public MapUpdate {
public:
    CharacterPosition(std::uint16_t,
                      std::uint16_t,
                      const std::string&,
                      const std::string&,
                      Dummy::Core::Character::Direction);

    virtual std::uint16_t code() override {
        return static_cast<std::uint16_t>(
            MapUpdateManager::Code::CHARACTER_POSITION
        );
    }

protected:
    virtual void _streamToPacket(OutgoingPacket&) const override;
    virtual void _streamFromPacket(IncomingPacket&) override;

private:
    std::uint16_t m_x, m_y;
    std::string m_name;
    std::string m_chipset;
    Dummy::Core::Character::Direction m_direction;
};

} // namespace Protocol

} // namespace Dummy
