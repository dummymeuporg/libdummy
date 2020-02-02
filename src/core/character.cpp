#include "dummy/core/character.hpp"

#include "dummy/core/errors.hpp"
#include "dummy/core/map.hpp"

#include <fstream>

namespace Dummy {
namespace Core {

Character::Character()
    : m_direction(Direction::DOWN)
{}

std::string Character::filename() const
{
    std::string filename(m_name);
    std::transform(filename.begin(), filename.end(), filename.begin(),
                   [](char c) {
                       if (::isalpha(c)) {
                           return static_cast<char>(::tolower(c));
                       } else if (c != '\'' && c != '-') {
                           return '_';
                       } else {
                           return c;
                       }
                   });
    return filename + ".dat";
}

Character& Character::setName(const std::string& name)
{
    m_name = Character::filteredName(name);
    return *this;
}

Character& Character::setSkin(const std::string& skin)
{
    m_skin = skin;
    return *this;
}

Character& Character::setPosition(const Position& position)
{
    m_position = position;
    std::cerr << "set position: " << position.first << " " << position.second
              << std::endl;
    return *this;
}

Character& Character::setMapLocation(const std::string& mapLocation)
{
    m_mapLocation = mapLocation;
    return *this;
}

Character& Character::setFloor(std::uint8_t floor)
{
    m_floor = floor;
    return *this;
}

Character& Character::setInstance(const std::string& instance)
{
    m_instance = instance;
    return *this;
}

std::string Character::filteredName(const std::string& name)
{
    std::string filteredName("");
    bool isPreviousAlpha   = false;
    bool isPreviousInvalid = false;
    for (const char& c : name) {
        if (::isalpha(c)) {
            filteredName += ! isPreviousAlpha ? ::toupper(c) : c;
            isPreviousAlpha   = true;
            isPreviousInvalid = false;
        } else {
            if (c == '\'' || c == '-') {
                filteredName += c;
                isPreviousInvalid = false;
                isPreviousAlpha   = false;
            } else if (c == ' ') {
                if (! isPreviousInvalid) {
                    filteredName += c;
                }
                isPreviousInvalid = false;
                isPreviousAlpha   = false;
            } else {
                isPreviousInvalid = true;
            }
        }
    }
    return filteredName;
}

void Character::_readFromStream(std::ifstream& ifs)
{
    std::uint32_t magicWord;
    std::uint32_t size;
    std::uint16_t word;
    std::string str;

    ifs.read(reinterpret_cast<char*>(&magicWord), sizeof(std::uint32_t));

    if (magicWord != Character::MAGIC_WORD) {
        throw WrongMagicNumber();
    }

    // read name
    ifs.read(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
    str.resize(size);
    ifs.read(str.data(), size);
    m_name = std::move(str);

    // read skin
    ifs.read(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
    str.resize(size);
    ifs.read(str.data(), size);
    m_skin = std::move(str);

    // read starting position
    ifs.read(reinterpret_cast<char*>(&word), sizeof(std::uint16_t));
    m_position.first = word;
    ifs.read(reinterpret_cast<char*>(&word), sizeof(std::uint16_t));
    m_position.second = word;

    // read map location.
    ifs.read(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
    str.resize(size);
    ifs.read(str.data(), size);
    m_mapLocation = std::move(str);

    // read direction
    ifs.read(reinterpret_cast<char*>(&m_direction), sizeof(std::uint8_t));

    // read floor
    ifs.read(reinterpret_cast<char*>(&m_floor), sizeof(std::uint8_t));

    // read instance
    ifs.read(reinterpret_cast<char*>(&size), sizeof(std::uint32_t));
    str.resize(size);
    ifs.read(str.data(), size);
    m_instance = std::move(str);
}

void Character::_writeToStream(std::ofstream& ofs) const
{
    std::uint32_t magicWord(Character::MAGIC_WORD);
    std::uint32_t nameSize(static_cast<std::uint32_t>(m_name.size()));
    std::uint32_t skinSize(static_cast<std::uint32_t>(m_skin.size()));
    std::uint32_t mapLocationSize(
        static_cast<std::uint32_t>(m_mapLocation.size()));
    std::uint32_t instanceSize(static_cast<std::uint32_t>(m_instance.size()));

    ofs.write(reinterpret_cast<const char*>(&magicWord), sizeof(std::uint32_t));
    ofs.write(reinterpret_cast<const char*>(&nameSize), sizeof(std::uint32_t));
    ofs.write(m_name.c_str(), static_cast<std::streamsize>(m_name.size()));
    ofs.write(reinterpret_cast<const char*>(&skinSize), sizeof(std::uint32_t));
    ofs.write(m_skin.c_str(), static_cast<std::streamsize>(m_skin.size()));
    ofs.write(reinterpret_cast<const char*>(&m_position.first),
              sizeof(std::uint16_t));
    ofs.write(reinterpret_cast<const char*>(&m_position.second),
              sizeof(std::uint16_t));
    ofs.write(reinterpret_cast<const char*>(&mapLocationSize),
              sizeof(std::uint32_t));
    ofs.write(m_mapLocation.c_str(),
              static_cast<std::streamsize>(m_mapLocation.size()));
    ofs.write(reinterpret_cast<const char*>(&m_direction),
              sizeof(std::uint8_t));
    ofs.write(reinterpret_cast<const char*>(&m_floor), sizeof(std::uint8_t));

    // Write instance.
    ofs.write(reinterpret_cast<const char*>(&instanceSize),
              sizeof(std::uint32_t));


    ofs.write(m_instance.c_str(),
              static_cast<std::streamsize>(m_instance.size()));
}

void Character::_writeToPacket(Protocol::OutgoingPacket& pkt) const
{
    pkt << m_name << m_skin << m_position.first << m_position.second
        << m_mapLocation << m_floor << m_instance;
}

void Character::_readFromPacket(Protocol::IncomingPacket& pkt)
{
    pkt >> m_name >> m_skin >> m_position.first >> m_position.second
        >> m_mapLocation >> m_floor >> m_instance;
}

} // namespace Core
} // namespace Dummy
