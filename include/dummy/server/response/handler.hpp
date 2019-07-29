#pragma once

namespace Dummy {
namespace Server {
namespace Response {

class Response;

class Handler {
public:
    virtual void handleResponse(const Response&) = 0;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
