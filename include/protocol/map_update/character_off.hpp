#pragma once

#include <string>
#include "protocol/map_update/update.hpp"

namespace Dummy {

namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

namespace MapUpdate {

class CharacterOff : public Update {
public:
    CharacterOff(const std::string&);

    virtual void accept(MapUpdateVisitor&) const override;
private:
    std::string m_name;
};

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
