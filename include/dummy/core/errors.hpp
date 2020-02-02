#pragma once

#include <exception>
#include <string>

namespace Dummy {
namespace Core {

class Error : public std::exception
{};


class LuaLoadFileError : public Error
{
public:
    LuaLoadFileError(const std::string& message)
        : m_message(message)
    {}
    virtual const char* what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

} // namespace Core
} // namespace Dummy
