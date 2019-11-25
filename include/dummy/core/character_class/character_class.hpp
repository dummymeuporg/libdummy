#pragma once

namespace Dummy {
namespace Core {

class Character;

namespace Spell {
class Spell;
};

namespace CharacterClass {

class CharacterClass {
public:
    CharacterClass(Character&, int);
    int attackCooldown() const {
        return m_attackCooldown;
    }

    virtual const Spell::Spell& attackSpell() const = 0;

protected:
    Character& m_character;
    int m_attackCooldown;
};

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
