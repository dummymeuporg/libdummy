#pragma once

#include <cstdint>

namespace Dummy {
namespace Server {
namespace Response {

class ResponseVisitor;

class Response {
public:
    Response();
    std::uint8_t status() const {
        return m_status;
    }

    void setStatus(std::uint8_t status);
    virtual void accept(ResponseVisitor&) const = 0;
private:
    std::uint8_t m_status;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
