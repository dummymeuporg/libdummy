#pragma once

#include <memory>

#include <dummy/server/response/response.hpp>

namespace Dummy {

namespace Server {
namespace Response {
namespace Spell {

class SpadassinAttack : public Response {
public:
    void accept(ResponseVisitor &) const override;
    std::shared_ptr<Response> clone() const override;
    void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    void readFrom(Dummy::Protocol::IncomingPacket&) override;
};

} // namespace Spell
} // namespace Response
} // namespace Server
} // namespace Dummy
