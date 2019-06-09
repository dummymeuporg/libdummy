#pragma once

#include <cstdint>
#include <string>
#include "protocol/map_update/update.hpp"
#include "core/character.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

class CharacterPosition : public Update {
public:
    CharacterPosition(std::uint16_t,
                      std::uint16_t,
                      const std::string&,
                      const std::string&,
                      Dummy::Core::Character::Direction);

        
    virtual void accept(MapUpdateVisitor&) const override;
private:
    std::uint16_t m_x, m_y;
    std::string m_name;
    std::string m_chipset;
    Dummy::Core::Character::Direction m_direction;
};

} // name MapUpdate

} // namespace Protocol

} // namespace Dummy
