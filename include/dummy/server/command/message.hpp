#pragma once
#include <string>

#include <dummy/server/command/command.hpp>

namespace Dummy {
namespace Server {
namespace Command {

class Message : public Command {
public:
    Message(const std::string&);
    void accept(CommandVisitor&) const override;
    const std::string& content() const {
        return m_content;
    }
private:
    std::string m_content;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
