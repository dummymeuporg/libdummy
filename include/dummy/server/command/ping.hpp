#pragma once

#include "dummy/server/command/command.hpp"

namespace Dummy {
namespace Server {
namespace Command {

class Ping : public Command
{
public:
    Ping();
    virtual void accept(CommandVisitor&) const override;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
