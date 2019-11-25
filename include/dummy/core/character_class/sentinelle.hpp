#pragma once

#include <dummy/core/character_class/character_class.hpp>
#include <dummy/core/spell/sentinelle_attack.hpp>

namespace Dummy {
namespace Core {
namespace CharacterClass {

class Sentinelle : public CharacterClass {
public:
    Sentinelle(Character&);

    virtual const Spell::Spell& attackSpell() const {
        return m_sentinelleAttack;
    }
private:
    Spell::SentinelleAttack m_sentinelleAttack;

};

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
