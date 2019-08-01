#include <dummy/server/command/command.hpp>

#include <dummy/server/response/response.hpp>
#include <dummy/server/game_session_communicator.hpp>

namespace Dummy {
namespace Server {

GameSessionCommunicator::GameSessionCommunicator(
    boost::asio::io_context& ioContext
) : m_ioContext(ioContext)
{}

GameSessionCommunicator::~GameSessionCommunicator() {}

void GameSessionCommunicator::setCommandHandler(
    std::shared_ptr<Dummy::Server::Command::Handler> commandHandler
) {
    m_commandHandler = commandHandler;
}

void GameSessionCommunicator::setResponseHandler(
    std::shared_ptr<Dummy::Server::Response::Handler> responseHandler
) {
    m_responseHandler = responseHandler;
}

void GameSessionCommunicator::forwardCommand(CommandPtr command) {
    boost::asio::post(m_ioContext, [this,
                                    self=shared_from_this(),
                                    command=command->shared_from_this()]()
    {
        auto ptr = m_commandHandler.lock();
        if (ptr) {
            ptr->handleCommand(command);
        }
    });
}

void GameSessionCommunicator::forwardResponse(ResponsePtr response) {
    boost::asio::post(m_ioContext,
                      [this,
                      self=shared_from_this(),
                      response=response->shared_from_this()]()
    {
        auto ptr = m_responseHandler.lock();
        if (ptr) {
            ptr->handleResponse(response);
        }
    });
}

void GameSessionCommunicator::closeFromClient() {
    m_responseHandler.reset();
    //m_commandHandler.detach();
}

void GameSessionCommunicator::closeFromServer() {
    m_commandHandler.reset();
    //m_responseHandler.detach();
}

} // namespace Server
} // namespace Dummy
