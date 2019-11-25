#pragma once

#include <memory>
#include <dummy/core/spell/spell.hpp>
#include <dummy/core/spell/spell_visitor.hpp>

namespace Dummy {
namespace Core {
namespace Spell {


class GrognardAttack : public Spell {
public:
    GrognardAttack();
    void accept(SpellVisitor& visitor) override {
        visitor.visitSpell(*this);
    }
};

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
