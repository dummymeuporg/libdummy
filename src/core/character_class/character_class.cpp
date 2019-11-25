#include <dummy/core/character_class/character_class.hpp>
#include <dummy/core/spell/spell.hpp>

namespace Dummy {
namespace Core {
namespace CharacterClass {

CharacterClass::CharacterClass(Character& character, int attackCooldown)
    : m_character(character),
      m_attackCooldown(attackCooldown)
{}

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
