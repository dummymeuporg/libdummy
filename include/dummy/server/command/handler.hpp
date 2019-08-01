#pragma once

#include <memory>

namespace Dummy {
namespace Server {
namespace Command {

class Command;

using CommandPtr = std::shared_ptr<const Dummy::Server::Command::Command>;

class Handler {
public:
    virtual void handleCommand(CommandPtr) = 0;
    virtual void responseHandlerClosed() = 0;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
