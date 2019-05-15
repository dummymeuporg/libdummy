#pragma once

#include <cstdint>
#include <string>
#include <tuple>

namespace Dummy {

namespace Core {

class Character {
public:
    using Position = std::tuple<std::uint16_t, std::uint16_t>;
    enum Direction { TOP = 0, RIGHT, DOWN, LEFT };

    Character();

    inline const std::string& name() const {
        return m_name;
    }

    inline const std::string& skin() const {
        return m_skin;
    }

    inline const std::string& mapLocation() const {
        return m_mapLocation;
    }

    inline const Direction& direction() const {
        return m_direction;
    }

    inline const Position& position() const {
        return m_position;
    }
private:
    std::string m_name;
    std::string m_skin;
    std::string m_mapLocation;
    Direction m_direction;
    Position m_position;
};

} // namespace Core

} // namespace Dummy