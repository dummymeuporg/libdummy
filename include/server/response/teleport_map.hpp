#pragma once

#include <memory>
#include "server/response/response.hpp"

namespace Dummy {
namespace Server {
namespace Response {

class TeleportMap : public Response {
public:
    virtual void accept(ResponseVisitor&) const override;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
