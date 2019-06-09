#pragma once

#include <memory>

#include "server/response/response.hpp"

namespace Dummy {
namespace Server {

namespace Response {

class MapUpdate : public Response {
public:
    virtual void accept(ResponseVisitor&) const override;
    
    virtual void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    virtual void readFrom(Dummy::Protocol::IncomingPacket&) override;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
