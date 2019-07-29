#pragma once
#include <dummy/server/command/command.hpp>

namespace Dummy {
namespace Server {
namespace Command {

class Message : public Command {
public:
    Message(const std::string&);
    void accept(CommandVisitor&) const override;
private:
    std::string m_content;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
