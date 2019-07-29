#pragma once

#include <memory>

namespace Dummy {
namespace Server {
namespace Response {

class Response;

using ResponsePtr = std::unique_ptr<const Response>;

class Handler {
public:
    virtual void handleResponse(ResponsePtr) = 0;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
