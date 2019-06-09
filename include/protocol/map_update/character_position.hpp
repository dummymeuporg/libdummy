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
                      const std::string&);

        
    virtual void accept(MapUpdateVisitor&) const override;

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }

    const std::string& name() const {
        return m_name;
    }

protected:
    std::uint16_t m_x, m_y;
    std::string m_name;
};

} // name MapUpdate

} // namespace Protocol

} // namespace Dummy
