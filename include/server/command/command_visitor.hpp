#pragma once

#include "server/errors.hpp"

namespace Dummy {
namespace Server {

namespace Response {
    class Response;
}

namespace Command {

class CommandNotHandled : public ::Dummy::Server::Error {
public:
    virtual const char* what() const noexcept override {
        return "this state does not handle such a command";
    };
};

class ConnectCommand;
class GetPrimaryInfoCommand;

class CommandVisitor {
public:
    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>    
    visitCommand(const ConnectCommand&) {
        throw CommandNotHandled();
    }

    virtual std::unique_ptr<const ::Dummy::Server::Response::Response>    
    visitCommand(const GetPrimaryInfoCommand&) {
        throw CommandNotHandled();
    }
};

} // namespace Command
} // namespace Server
} // namespace Dummy
