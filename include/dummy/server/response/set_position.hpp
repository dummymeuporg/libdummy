#pragma once

#include <memory>

#include <dummy/server/response/response.hpp>

namespace Dummy {

namespace Core {
class Character;
} // namespace Core

namespace Server {
namespace Response {

class SetPosition : public Response {
public:
    void accept(ResponseVisitor&) const override;
    void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    void readFrom(Dummy::Protocol::IncomingPacket&) override;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
