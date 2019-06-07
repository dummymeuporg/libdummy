#pragma once

#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Response {

class ConnectResponse : public Response {
public:
    virtual void accept(ResponseVisitor&) const override;
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
