#pragma once

#include <string>

#include "dummy/server/command/command.hpp"
#include "dummy/utils/dummy_types.hpp"

namespace Dummy {
namespace Server {
namespace Command {

class TeleportMap : public Command
{
public:
    TeleportMap(const std::string&, tilecoords, uint8_t, const std::string&);
    TeleportMap(const std::string&, uint16_t, uint16_t, uint8_t,
                const std::string&);
    virtual ~TeleportMap();

    virtual void
    accept(::Dummy::Server::Command::CommandVisitor&) const override;

    const std::string& mapName() const { return m_mapName; }
    tilecoords destination() const { return m_destination; }
    uint16_t x() const { return m_destination.first; }
    uint16_t y() const { return m_destination.second; }
    uint8_t floor() const { return m_floor; }
    const std::string& instance() const { return m_instance; }

private:
    std::string m_mapName;
    tilecoords m_destination;
    uint8_t m_floor;
    std::string m_instance;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
