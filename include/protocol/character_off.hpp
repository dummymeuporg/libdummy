#pragma once

#include <string>
#include "protocol/map_update.hpp"

namespace Dummy {

namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

class CharacterOff : public MapUpdate {
public:
    CharacterOff(const std::string&);

protected:
    virtual void _streamToPacket(OutgoingPacket&) const override;
    virtual void _streamFromPacket(IncomingPacket&) override;

private:
    std::string m_name;
};

} // namespace Protocol

} // namespace Dummy
