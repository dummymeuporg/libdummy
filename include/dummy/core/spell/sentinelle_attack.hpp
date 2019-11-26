#pragma once

#include <dummy/core/spell/spell.hpp>
#include <dummy/core/spell/spell_visitor.hpp>

namespace Dummy {
namespace Core {
namespace Spell {


class SentinelleAttack : public Spell {
public:
    SentinelleAttack();
    void accept(SpellVisitor& visitor) const override {
        visitor.visitSpell(*this);
    }
};

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
