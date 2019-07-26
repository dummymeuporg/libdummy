#pragma once

#include <memory>

#include <dummy/server/response/response.hpp>

namespace Dummy {

namespace Core {
class Character;
} // namespace Core

namespace Server {
namespace Response {

class SelectCharacter : public Response {
public:
    virtual void accept(ResponseVisitor&) const override;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
