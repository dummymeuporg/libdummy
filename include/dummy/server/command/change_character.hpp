#pragma once

#include <dummy/server/command/command.hpp>

namespace Dummy {
namespace Server {
namespace Command {

class ChangeCharacter : public Command {
public:
    void accept(::Dummy::Server::Command::CommandVisitor &) const override;
};

}
}
}
