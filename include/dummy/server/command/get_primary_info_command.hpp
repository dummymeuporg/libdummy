#pragma once

#include <string>

#include "dummy/server/command/command.hpp"

namespace Dummy {
namespace Server {
namespace Command {

class GetPrimaryInfoCommand : public Command
{
public:
    GetPrimaryInfoCommand();
    virtual void
    accept(::Dummy::Server::Command::CommandVisitor&) const override;

private:
};

} // namespace Command
} // namespace Server
} // namespace Dummy
