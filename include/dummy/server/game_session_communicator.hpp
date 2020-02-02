#pragma once

#include <boost/asio.hpp>

#include "dummy/server/command/handler.hpp"
#include "dummy/server/response/handler.hpp"

namespace Dummy {
namespace Server {

using CommandPtr  = std::shared_ptr<const Dummy::Server::Command::Command>;
using ResponsePtr = std::shared_ptr<const Dummy::Server::Response::Response>;

class GameSessionCommunicator
    : public std::enable_shared_from_this<GameSessionCommunicator>
{
public:
    GameSessionCommunicator(boost::asio::io_context&);
    virtual ~GameSessionCommunicator();

    void forwardCommand(CommandPtr);
    void forwardResponse(ResponsePtr);

    void setCommandHandler(std::shared_ptr<Dummy::Server::Command::Handler>);
    void setResponseHandler(std::shared_ptr<Dummy::Server::Response::Handler>);

    void closeFromCommandHandler();
    void closeFromResponseHandler();

private:
    boost::asio::io_context& m_ioContext;
    std::weak_ptr<Dummy::Server::Command::Handler> m_commandHandler;
    std::weak_ptr<Dummy::Server::Response::Handler> m_responseHandler;
};

} // namespace Server
} // namespace Dummy
