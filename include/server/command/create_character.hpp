#pragma once

#include <string>

#include "server/command/command.hpp"

namespace Dummy {
namespace Server {
namespace Command {

class CreateCharacter : public Command {
public:
    CreateCharacter(const std::string&, const std::string&);
    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>
    accept(::Dummy::Server::Command::CommandVisitor&) const override;

    const std::string& name() const {
        return m_name;
    }

    const std::string& skin() const {
        return m_skin;
    }
private:
    std::string m_name;
    std::string m_skin;
};

} // namespace Command
} // namespace Server
} // namespace Dummy