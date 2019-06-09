#pragma once

#include <cstdint>
#include <string>
#include "protocol/map_update/character_position.hpp"
#include "core/character.hpp"

namespace Dummy {

namespace Protocol {

namespace MapUpdate {

class CharacterOn : public CharacterPosition {
public:
    CharacterOn(std::uint16_t,
                std::uint16_t,
                const std::string&,
                const std::string&,
                Dummy::Core::Character::Direction);
 
    virtual void accept(MapUpdateVisitor&) const override;

    const std::string& chipset() const {
        return m_chipset;
    }

    Dummy::Core::Character::Direction direction() const {
        return m_direction;
    }
protected:
    std::string m_chipset;
    Dummy::Core::Character::Direction m_direction;
};

} // name MapUpdate

} // namespace Protocol

} // namespace Dummy
