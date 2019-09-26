#pragma once

#include <dummy/server/command/command.hpp>

namespace Dummy {
namespace Server {
namespace Command {

class SetPosition : public Command {
public:
    SetPosition(std::uint16_t, std::uint16_t);
    void accept(CommandVisitor&) const override;

    std::uint16_t x() const {
        return m_x;
    }

    std::uint16_t y() const {
        return m_y;
    }
private:
    std::uint16_t m_x, m_y;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
