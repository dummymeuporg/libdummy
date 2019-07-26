#pragma once

#include <memory>

namespace Dummy {
namespace Server {

namespace Response {
    class Response;
}

namespace Command {

class CommandVisitor;

class Command {
public:
    Command() {}
    virtual void accept(::Dummy::Server::Command::CommandVisitor&) const = 0;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
