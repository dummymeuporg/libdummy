#include "core/character.hpp"

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

} // namespace Core

} // namespace Dummy
