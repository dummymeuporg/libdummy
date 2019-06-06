#pragma once

#include <cstdint>

namespace Dummy {
namespace Server {
namespace Response {

class ResponseVisitor;

class Response {
public:
    enum class Status : std::uint16_t {
        OK = 0,
        ERROR = 1
    };
    Response();
    Status status() const {
        return m_status;
    }

    void setStatus(Status status);
    virtual void accept(ResponseVisitor&) const = 0;
private:
    Status m_status;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
