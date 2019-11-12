#pragma once

namespace Dummy {
namespace Core {
namespace CharacterClass {

class CharacterClass {
public:
    CharacterClass(int);
    int attackCooldown() const {
        return m_attackCooldown;
    }
protected:
    int m_attackCooldown;
};

} // namespace CharacterClass
} // namespace Core
} // namespace Dummy
