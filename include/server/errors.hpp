#pragma once

#include <exception>

namespace Dummy {
namespace Server {

class Error : public std::exception {

};

class GameServerError : public Error {
public:
    enum Code {
        OK = 0,
        CHARACTER_ALREADY_EXISTS, /* 1 */
        SKIN_DOES_NOT_EXIST,      /* 2 */
        INVALID_SESSION_ID,       /* 3 */
        ACCOUNT_NOT_PENDING,      /* 4 */
        ALREADY_CONNECTED,        /* 5 */

        COUNT
    };

    virtual Code code() const = 0;

};

class CharacterAlreadyExists : public GameServerError {
public:
    virtual Code code() const override {
        return GameServerError::Code::CHARACTER_ALREADY_EXISTS;
    }

    virtual const char* what() const noexcept override {
        return "the character already exists";
    }
};


class SkinDoesNotExist : public GameServerError {
public:
    virtual Code code() const override {
        return GameServerError::Code::SKIN_DOES_NOT_EXIST;
    }
    virtual const char* what() const noexcept override {
        return "the skin does not exist";
    }
};

class InvalidSessionID : public GameServerError {
public:
    virtual Code code() const override {
        return GameServerError::Code::INVALID_SESSION_ID;
    }

    virtual const char* what() const noexcept override {
        return "the session ID is invalid";
    }
};

class AccountNotPending : public GameServerError {
public:
    virtual Code code() const override {
        return GameServerError::Code::ACCOUNT_NOT_PENDING;
    }

    virtual const char* what() const noexcept override {
        return "the account is not pending";
    }
};

class AlreadyConnected : public GameServerError {
public:
    virtual Code code() const override {
        return GameServerError::Code::ALREADY_CONNECTED;
    }

    virtual const char* what() const noexcept override {
        return "the account is already connected";
    }
};

} // namespace Server
} // namespace Dummy
