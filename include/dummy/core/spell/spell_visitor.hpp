#pragma once

namespace Dummy {
namespace Core {
namespace Spell {

class GrognardAttack;
class SentinelleAttack;
class SpadassinAttack;

class SpellVisitor {
public:
    virtual void visitSpell(const GrognardAttack&) = 0;
    virtual void visitSpell(const SentinelleAttack&) = 0;
    virtual void visitSpell(const SpadassinAttack&) = 0;

};

}
}
}
