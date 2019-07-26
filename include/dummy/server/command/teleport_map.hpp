#pragma once

#include <string>
#include <dummy/server/command/command.hpp>

namespace Dummy {
namespace Server {
namespace Command {

class TeleportMap : public Command {
public:
    TeleportMap(const std::string&,
                const std::pair<std::uint16_t, std::uint16_t>&,
                const std::string&);
    TeleportMap(const std::string&,
                std::uint16_t, std::uint16_t, const std::string&);
    virtual ~TeleportMap();

    virtual void
    accept(::Dummy::Server::Command::CommandVisitor&) const override;

    const std::string& mapName() const {
        return m_mapName;
    }

    const std::pair<std::uint16_t, std::uint16_t> destination() const {
        return m_destination;
    }

    const std::string& instance() const {
        return m_instance;
    }
private:
    std::string m_mapName;
    std::pair<std::uint16_t, std::uint16_t> m_destination;
    std::string m_instance;
};

} // namespace Command
} // namespace Server
} // namespace Dummy
