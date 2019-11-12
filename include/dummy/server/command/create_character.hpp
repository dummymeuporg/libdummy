#pragma once

#include <string>

#include <dummy/core/character.hpp>
#include <dummy/server/command/command.hpp>

namespace Dummy {
namespace Server {
namespace Command {

class CreateCharacter : public Command {
public:
    CreateCharacter(
        const std::string&,
        const std::string&,
        Dummy::Core::Character::Class);
    virtual void
    accept(::Dummy::Server::Command::CommandVisitor&) const override;

    const std::string& name() const {
        return m_name;
    }

    const std::string& skin() const {
        return m_skin;
    }

    Dummy::Core::Character::Class characterClass() const {
        return m_class;
    }
private:
    std::string m_name;
    std::string m_skin;
    Dummy::Core::Character::Class m_class;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
