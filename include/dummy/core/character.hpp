#pragma once

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <tuple>


#include <dummy/core/character_class/character_class.hpp>

#include <dummy/protocol/incoming_packet.hpp>
#include <dummy/protocol/outgoing_packet.hpp>


namespace Dummy {

namespace Core {


class Character {
public:
    static const uint32_t MAGIC_WORD = 0xdeadface;
    using Position = std::pair<std::uint16_t, std::uint16_t>;
    enum class Direction : std::uint8_t {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3
    };

    enum class Class : std::uint8_t {
        NONE = 0,
        GROGNARD = 1,
        SENTINELLE = 2,
        SPADASSIN = 3
    };

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
        std::cerr << "position():" << m_position.first << ", "
                  << m_position.second << std::endl;
        return m_position;
    }

    inline std::uint8_t floor() const {
        return m_floor;
    }

    const std::string& instance() const {
        return m_instance;
    }

    Class characterClass() const {
        return m_class;
    }

    const CharacterClass::CharacterClass& getCharacterClass() const {
        return *m_characterClass;
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

    friend Dummy::Protocol::OutgoingPacket&
    operator<<(Protocol::OutgoingPacket& pkt, const Character& chr) {
        chr._writeToPacket(pkt);
        return pkt;
    }

    friend Dummy::Protocol::IncomingPacket&
    operator>>(Protocol::IncomingPacket& pkt, Character& chr) {
        chr._readFromPacket(pkt);
        return pkt;
    }

    Character& setName(const std::string&);
    Character& setSkin(const std::string&);
    Character& setPosition(const Position&);
    Character& setMapLocation(const std::string&);
    Character& setFloor(std::uint8_t);
    Character& setInstance(const std::string&);
    Character& setClass(Class);
private:
    /* Methods. */
    void _writeToStream(std::ofstream&) const;
    void _readFromStream(std::ifstream&);
    void _writeToPacket(Protocol::OutgoingPacket&) const;
    void _readFromPacket(Protocol::IncomingPacket&);
    void instantiateCharacterClass();

    /* Attributes. */
    std::string m_name;
    std::string m_skin;
    std::string m_mapLocation;
    Direction m_direction;
    Position m_position;
    std::uint8_t m_floor;
    std::string m_instance;
    Class m_class;
    std::shared_ptr<CharacterClass::CharacterClass> m_characterClass;
};

} // namespace Core

} // namespace Dummy
