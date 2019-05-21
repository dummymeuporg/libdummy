#pragma once

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <string>
#include <tuple>

namespace Dummy {

namespace Core {

class Character {
public:
    static const uint32_t MAGIC_WORD = 0xdeadface;
    using Position = std::tuple<std::uint16_t, std::uint16_t>;
    enum Direction { TOP = 0, RIGHT, DOWN, LEFT };

    Character();

    static std::string filteredName(const std::string&);

    inline const std::string& name() const {
        return m_name;
    }

    std::string filename() const;

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

    friend std::ifstream&
    operator>>(std::ifstream& ifs, Character& chr) {
        chr._readFromStream(ifs);
        return ifs;
    }

    friend std::ofstream&
    operator<<(std::ofstream& ofs, const Character& chr) {
        chr._writeToStream(ofs);
        return ofs;
    }

    Character& setName(const std::string&);
private:
    void _writeToStream(std::ofstream&) const;
    void _readFromStream(std::ifstream&);
    std::string m_name;
    std::string m_skin;
    std::string m_mapLocation;
    Direction m_direction;
    Position m_position;
};

} // namespace Core

} // namespace Dummy
