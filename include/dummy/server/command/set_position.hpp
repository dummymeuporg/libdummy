#pragma once

#include "dummy/server/command/command.hpp"
#include "dummy/utils/dummy_types.hpp"

namespace Dummy {
namespace Server {
namespace Command {

class SetPosition : public Command
{
public:
    SetPosition(tilecoords);
    void accept(CommandVisitor&) const override;

    tilecoords pos() const { return m_xy; }

private:
    tilecoords m_xy;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
