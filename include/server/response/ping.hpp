#pragma once

#include <memory>
#include <vector>

#include "server/response/response.hpp"

namespace Dummy {
namespace Protocol {
namespace MapUpdate {
class Update;
} // namespace MapUpdate
} // namespace Protocol
namespace Server {
namespace Response {

class ResponseVisitor;

class Ping : public Response {
public:
    virtual void accept(ResponseVisitor&) const override;
    void addUpdate(std::unique_ptr<Dummy::Protocol::MapUpdate::Update>);
private:
    std::vector<std::unique_ptr<Dummy::Protocol::MapUpdate::Update>>
        m_mapUpdates;

};

} // namespace Response
} // namespace Server
} // namespace Dummy
