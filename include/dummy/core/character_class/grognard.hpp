#pragma once

#include <dummy/core/character_class/character_class.hpp>
#include <dummy/core/spell/grognard_attack.hpp>

namespace Dummy {
namespace Core {
namespace CharacterClass {

class Grognard : public CharacterClass {
public:
    Grognard(Character&);

    virtual const Spell::Spell& attackSpell() const {
        return m_grognardAttack;
    }
private:
    Spell::GrognardAttack m_grognardAttack;
};

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
