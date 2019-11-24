#pragma once


#include <dummy/server/command/command.hpp>

namespace Dummy {
namespace Server {
namespace Command {
namespace Spell {


class SpadassinAttack : public Command {
public:
    SpadassinAttack(std::uint8_t);
    void accept(::Dummy::Server::Command::CommandVisitor &) const override;
private:
    std::uint8_t m_direction;
};

} // namespace Spell
} // namespace Command
} // namespace Server
} // namespace Dummy
