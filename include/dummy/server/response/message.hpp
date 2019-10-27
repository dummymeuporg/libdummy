#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <dummy/server/response/response.hpp>

namespace Dummy {
namespace Server {
namespace Response {

class Message : public Response {
public:
    void accept(ResponseVisitor&) const override;
    std::shared_ptr<Response> clone() const override;
    void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    void readFrom(Dummy::Protocol::IncomingPacket&) override;

    std::uint32_t author() const {
        return m_author;
    }

    const std::string& content() const {
        return m_content;
    }

    void setAuthor(std::uint32_t);
    void setContent(const std::string&);
private:
    std::uint32_t m_author;
    std::string m_content;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
