#pragma once

#include <cstdint>
#include <string>
#include <utility>

#include <boost/asio.hpp>

#include <dummy/server/map_observer.hpp>

namespace Dummy {

namespace Core {
class Foe;
} // namespace Core


namespace Server {

class Foe : public MapObserver {
public:
    Foe(const Core::Foe&, boost::asio::io_context&);

    const std::string& chipset() const {
        return m_chipset;
    }

    std::uint16_t x() const {
        return m_position.first;
    }

    std::uint16_t y() const {
        return m_position.second;
    }

    std::uint8_t floor() const {
        return m_floor;
    }

    void notifyOn(MapUpdatesVector&) override;
    void notifyPosition(MapUpdatesVector&) override;
    void receiveMessage(std::uint32_t, const std::string&) override;
    std::pair<std::uint16_t, std::uint16_t> position() override;


private:
    boost::asio::io_context& m_ioContext;
    std::string m_name;
    std::string m_chipset;
    std::pair<std::uint16_t, std::uint16_t> m_position;
    std::uint8_t m_floor;
};
} // namespace Server
} // namespace Dummy
