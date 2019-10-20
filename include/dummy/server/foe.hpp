#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace Dummy {

namespace Core {
class Foe;
} // namespace Core


namespace Server {

class Foe {
public:
    Foe() {}
    Foe(const Core::Foe&, const std::string&);

    const std::string& name() const {
        return m_name;
    }

    const std::string& chipset() const {
        return m_chipset;
    }

    std::uint16_t x() const {
        return m_position.first;
    }

    std::uint16_t y() const {
        return m_position.second;
    }

    std::uint8_t floor() const {
        return m_floor;
    }

private:
    std::string m_name;
    std::string m_chipset;
    std::pair<std::uint16_t, std::uint16_t> m_position;
    std::uint8_t m_floor;
};
} // namespace Server
} // namespace Dummy
