#pragma once

#include <memory>

namespace Dummy {

namespace Server {
namespace Command {
class Command;
}
}

namespace Core {

namespace Spell {

class SpellVisitor;

class Spell {
public:
    Spell();
    virtual void accept(SpellVisitor&) = 0;
};

} // namespace Spell
} // namespace Core
} // namespace Dummy
