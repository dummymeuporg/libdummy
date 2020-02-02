#pragma once

#include "dummy/core/character.hpp"
#include "dummy/server/game_session.hpp"
#include "dummy/server/map_observer.hpp"

namespace Dummy {
namespace Server {

class Account;
class Instance;
class Map;

class Player : public MapObserver
{
public:
    Player(GameSession&, std::shared_ptr<::Dummy::Core::Character>);

    GameSession& gameSession() { return m_gameSession; }

    std::shared_ptr<::Dummy::Core::Character> character() const
    {
        return m_character;
    }

    const std::string& name() const { return m_character->name(); }

    const std::pair<std::uint16_t, std::uint16_t> serverPosition() const
    {
        return m_character->position();
    }

    std::weak_ptr<Map> map() const { return m_map; }

    std::weak_ptr<Instance> instance() const { return m_instance; }

    void setMap(std::weak_ptr<Map>);
    void setPosition(const std::pair<std::uint16_t, std::uint16_t>&);
    void setPosition(std::uint16_t, std::uint16_t);
    void setInstance(std::weak_ptr<Instance>);
    void leaveCurrentMap();

    void notifyOn(MapUpdatesVector&) override;
    void notifyPosition(MapUpdatesVector&) override;
    void receiveMessage(std::uint32_t, const std::string&) override;
    std::pair<std::uint16_t, std::uint16_t> position() override;

private:
    GameSession& m_gameSession;
    std::shared_ptr<Dummy::Core::Character> m_character;
    std::weak_ptr<Map> m_map;
    std::weak_ptr<Instance> m_instance;
};

} // namespace Server
} // namespace Dummy
