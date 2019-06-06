#pragma once

#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Response {

class ConnectResponse : public Response {
public:
    virtual void accept(ResponseVisitor&) const override;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
