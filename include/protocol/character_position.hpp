#pragma once

#include <cstdint>
#include <string>
#include "protocol/map_update.hpp"

namespace Dummy {

namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

class CharacterPosition : public MapUpdate {
public:
    CharacterPosition(std::uint16_t,
                      std::uint16_t,
                      const std::string&,
                      const std::string&);

protected:
    virtual void _streamToPacket(OutgoingPacket&) const override;
    virtual void _streamFromPacket(IncomingPacket&) override;

private:
    std::uint16_t m_x, m_y;
    std::string m_name;
    std::string m_chipset;
};

} // namespace Protocol

} // namespace Dummy
