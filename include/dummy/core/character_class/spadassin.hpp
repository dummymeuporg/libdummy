#pragma once

#include <dummy/core/character_class/character_class.hpp>
#include <dummy/core/spell/spadassin_attack.hpp>


namespace Dummy {
namespace Core {
namespace CharacterClass {

class Spadassin : public CharacterClass {
public:
    Spadassin(Character&);

    virtual const Spell::Spell& attackSpell() const {
        return m_spadassinAttack;
    }
private:
    Spell::SpadassinAttack m_spadassinAttack;

};

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
