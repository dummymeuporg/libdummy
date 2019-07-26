#pragma once

#include <string>
#include <dummy/protocol/map_update/update.hpp>

namespace Dummy {

namespace Protocol {

class IncomingPacket;
class OutgoingPacket;

namespace MapUpdate {

class CharacterOff : public Update {
public:
    CharacterOff(const std::string&);

    virtual void accept(MapUpdateVisitor&) const override;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;

    const std::string& name() const {
        return m_name;
    }
private:
    std::string m_name;
};

} // namespace MapUpdate

} // namespace Protocol

} // namespace Dummy
