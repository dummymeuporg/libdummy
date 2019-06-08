#pragma once

#include <string>

#include "server/command/command.hpp"

namespace Dummy {
namespace Server {
namespace Command {

class SelectCharacter : public Command {
public:
    SelectCharacter(const std::string&);
    virtual void
    accept(::Dummy::Server::Command::CommandVisitor&) const override;

    const std::string& name() const {
        return m_name;
    }
private:
    std::string m_name;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
