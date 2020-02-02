#pragma once

#include "dummy/server/response/characters_list_response.hpp"

namespace Dummy {
namespace Server {
namespace Response {

using Position = std::pair<std::uint16_t, std::uint16_t>;
class ChangeCharacter : public Response {
public:
    ChangeCharacter();
    void accept(ResponseVisitor&) const override;
    std::shared_ptr<Response> clone() const override;
    void serializeTo(Dummy::Protocol::OutgoingPacket&) const override;
    void readFrom(Dummy::Protocol::IncomingPacket&) override;
    const std::string& mapLocation() const {
        return m_mapLocation;
    }
    const std::pair<std::uint16_t, std::uint16_t>& position() const {
        return m_position;
    }
    void setMapLocation(const std::string&);
    void setPosition(const Position&);
private:
    std::string m_mapLocation;
    Position m_position;
};

} // namespace Response
} // namespace Server
} // namespace Dummy
