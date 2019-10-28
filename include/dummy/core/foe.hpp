#pragma once

#include <string>

namespace Dummy {
namespace Core {

class Foe {
public:
    Foe(const std::string&);
    const std::string& luaFilename() const {
        return m_luaFilename;
    }

private:
    std::string m_luaFilename;
};

} // namespace Core
} // namespace Dummy
