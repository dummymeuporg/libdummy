#pragma once

#include <string>

#include "server/command/command.hpp"

namespace Dummy {
namespace Server {
namespace Command {

class GetPrimaryInfoCommand : public Command {
public:
    GetPrimaryInfoCommand();
    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    accept(::Dummy::Server::Command::CommandVisitor&) const override;
private:
};

} // namespace Command
} // namespace Server
} // namespace Dummy
