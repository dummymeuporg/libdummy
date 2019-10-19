#pragma once

#include <memory>
#include <vector>

#include <dummy/server/response/response.hpp>

namespace Dummy {
namespace Protocol {
namespace MapUpdate {
class Update;
class CharacterFloor;
class CharacterOn;
class CharacterOff;
class CharacterPosition;
} // namespace MapUpdate
} // namespace Protocol
namespace Server {
namespace Response {

class ResponseVisitor;

using MapUpdates = \
    std::vector<std::shared_ptr<const Dummy::Protocol::MapUpdate::Update>>;


class Ping : public Response {
public:
    virtual void accept(ResponseVisitor&) const override;
    std::shared_ptr<Response> clone() const override;
    void addUpdate(std::shared_ptr<const Dummy::Protocol::MapUpdate::Update>);
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;
    const MapUpdates& mapUpdates() const {
        return m_mapUpdates;
    }
private:
    std::shared_ptr<const Dummy::Protocol::MapUpdate::CharacterOff>
    readCharacterOff(Dummy::Protocol::IncomingPacket&);

    std::shared_ptr<const Dummy::Protocol::MapUpdate::CharacterOn>
    readCharacterOn(Dummy::Protocol::IncomingPacket&);

    std::shared_ptr<const Dummy::Protocol::MapUpdate::CharacterPosition>
    readCharacterPosition(Dummy::Protocol::IncomingPacket&);

    std::shared_ptr<const Dummy::Protocol::MapUpdate::CharacterFloor>
    readCharacterFloor(Dummy::Protocol::IncomingPacket&);

    MapUpdates m_mapUpdates;

};

} // namespace Response
} // namespace Server
} // namespace Dummy
