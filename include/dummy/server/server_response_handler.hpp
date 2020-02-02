#pragma once

namespace Dummy {
namespace Server {

class ServerResponseHandler {
public:
    virtual ~ServerResponseHandler();
    virtual void dequeueResponse() = 0;
};

} // namespace Server
} // namespace Dummy
