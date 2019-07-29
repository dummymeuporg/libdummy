#pragma once

#include <memory>

#include <dummy/server/response/response.hpp>

namespace Dummy {
namespace Server {
namespace Response {

class Message : public Response {
public:
    void accept(ResponseVisitor&) const override;
    void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    void readFrom(Dummy::Protocol::IncomingPacket&) override;

    const std::string& author() const {
        return m_author;
    }

    const std::string& content() const {
        return m_content;
    }

    void setAuthor(const std::string&);
    void setContent(const std::string&);
private:
    std::string m_author, m_content;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
