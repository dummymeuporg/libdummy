#pragma once

#include <cstdint>
#include <dummy/protocol/living.hpp>

namespace Dummy {

namespace Protocol {

class NamedLiving : public Living {
public:
    NamedLiving(std::uint16_t,
                std::uint16_t,
                const std::string&,
                const std::string&,
                Dummy::Core::Character::Direction);

    inline const std::string& name() const {
        return m_name;
    }

    void setName(const std::string&);
private:
    std::string m_name;
};

} // namespace Protocol
} // namespace Dummy
