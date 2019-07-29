#pragma once

namespace Dummy {
namespace Server {
namespace Command {

class Command;

class Handler {
public:
    virtual void handleCommand(const Command&) = 0;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
