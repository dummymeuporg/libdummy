#include "core/character.hpp"
#include "core/errors.hpp"


namespace Dummy {

namespace Core {

Character::Character()
{

}

std::string Character::filename() const {
    std::string filename(m_name);
    std::transform(
        filename.begin(),
        filename.end(),
        filename.begin(),
        [](char c) {
            if (::isalpha(c)) {
                return static_cast<char>(::tolower(c));
            } else if (c != '\'' && c != '-') {
                return '_';
            } else {
                return c;
            }
        }
    );
    return filename + ".dat";
}

Character& Character::setName(const std::string& name) {
    m_name = std::move(Character::filteredName(name));
    return *this;
}

Character& Character::setSkin(const std::string& skin) {
    m_skin = skin;
    return *this;
}

Character& Character::setPosition(const Position& position) {
    m_position = position;
    return *this;
}

Character& Character::setMapLocation(const std::string& mapLocation) {
    m_mapLocation = mapLocation;
    return *this;
}

std::string Character::filteredName(const std::string& name) {
    std::string filteredName("");
    bool isPreviousAlpha = false;
    bool isPreviousInvalid = false;
    for(const char& c: name) {
        if (::isalpha(c)) {
            filteredName += !isPreviousAlpha ? ::toupper(c) : c;
            isPreviousAlpha = true;
            isPreviousInvalid = false;
        } else {
            if (c == '\'' || c == '-') {
                filteredName += c;
                isPreviousInvalid = false;
                isPreviousAlpha = false;
            } else if(c == ' ') {
                if (!isPreviousInvalid) {
                    filteredName += c;
                }
                isPreviousInvalid = false;
                isPreviousAlpha = false;
            } else {
                isPreviousInvalid = true;
            }
        }
    }
    return filteredName;
}

void Character::_readFromStream(std::ifstream& ifs) {
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

}

void Character::_writeToStream(std::ofstream& ofs) const {
    std::uint32_t magicWord(Character::MAGIC_WORD);
    std::uint32_t nameSize(static_cast<std::uint32_t>(m_name.size()));
    std::uint32_t skinSize(static_cast<std::uint32_t>(m_skin.size()));
    std::uint32_t mapLocationSize(static_cast<std::uint32_t>(
        m_mapLocation.size()
    ));

    ofs.write(reinterpret_cast<const char*>(&magicWord),
              sizeof(std::uint32_t));
    ofs.write(reinterpret_cast<const char*>(&nameSize), sizeof(std::uint32_t));
    ofs.write(m_name.c_str(), m_name.size());
    ofs.write(reinterpret_cast<const char*>(&skinSize), sizeof(std::uint32_t));
    ofs.write(m_skin.c_str(), m_skin.size());
    ofs.write(reinterpret_cast<const char*>(&m_position.first),
              sizeof(std::uint16_t));
    ofs.write(reinterpret_cast<const char*>(&m_position.second),
              sizeof(std::uint16_t));
    ofs.write(reinterpret_cast<const char*>(&mapLocationSize),
              sizeof(std::uint32_t));
    ofs.write(m_mapLocation.c_str(), m_mapLocation.size());
}

void Character::_writeToPacket(Protocol::OutgoingPacket& pkt) const {
    pkt << m_name << m_skin << m_position.first << m_position.second
        << m_mapLocation;
}

void Character::_readFromPacket(Protocol::IncomingPacket& pkt) {
    pkt >> m_name >> m_skin >> m_position.first >> m_position.second
        >> m_mapLocation;
}

} // namespace Core

} // namespace Dummy
