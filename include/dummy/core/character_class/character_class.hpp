#pragma once

namespace Dummy {
namespace Core {
class Character;
namespace CharacterClass {

class CharacterClass {
public:
    CharacterClass(Character&, int);
    int attackCooldown() const {
        return m_attackCooldown;
    }
protected:
    Character& m_character;
    int m_attackCooldown;
};

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
