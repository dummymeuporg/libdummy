#pragma once

#include <memory>

namespace Dummy {
namespace Server {
namespace Response {

class Response;

using ResponsePtr = std::shared_ptr<const Response>;

class Handler : public std::enable_shared_from_this<Handler> {
public:
    virtual void handleResponse(ResponsePtr) = 0;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
