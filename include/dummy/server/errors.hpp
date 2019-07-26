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
        ACCOUNT_NOT_PENDING,      /* 1 */
        ALREADY_CONNECTED,        /* 2 */
        INVALID_SESSION_ID,       /* 3 */

        COUNT
    };

    virtual int code() const = 0;

};

class CreateCharacterError : public GameServerError {
public:
    enum Code {
        OK = 0,
        TOO_MUCH_CHARACTERS,      /* 1 */
        INVALID_SKIN,             /* 2 */
        NAME_ALREADY_TAKEN,       /* 3 */
        NAME_EMPTY,               /* 4 */

        COUNT
    };
};

class SelectCharacterError : public GameServerError {
public:
    enum Code {
        OK = 0,
        CHARACTER_NOT_FOUND,     /* 1 */

        COUNT
    };
};

class CharacterNotFound : public GameServerError {
    virtual int code() const override {
        return CreateCharacterError::Code::TOO_MUCH_CHARACTERS;
    }

    virtual const char* what() const noexcept override {
        return "the character does not exist.";
    }
};


class TooMuchCharacters : public CreateCharacterError {
public:
    virtual int code() const override {
        return CreateCharacterError::Code::TOO_MUCH_CHARACTERS;
    }
};

class NameAlreadyTaken : public CreateCharacterError {
public:
    virtual int code() const override {
        return CreateCharacterError::Code::NAME_ALREADY_TAKEN;
    }

    virtual const char* what() const noexcept override {
        return "the character already exists";
    }
};

class CharacterNameEmpty : public CreateCharacterError {
public:
    int code() const override {
        return CreateCharacterError::Code::NAME_EMPTY;
    }

    const char* what() const noexcept override {
        return "the character name is empty";
    }
};

class InvalidSkin : public CreateCharacterError {
public:
    virtual int code() const override {
        return CreateCharacterError::Code::INVALID_SKIN;
    }
    virtual const char* what() const noexcept override {
        return "the skin is invalid";
    }
};

class InvalidSessionID : public GameServerError {
public:
    virtual int code() const override {
        return GameServerError::Code::INVALID_SESSION_ID;
    }

    virtual const char* what() const noexcept override {
        return "the session ID is invalid";
    }
};

class AccountNotPending : public GameServerError {
public:
    virtual int code() const override {
        return GameServerError::Code::ACCOUNT_NOT_PENDING;
    }

    virtual const char* what() const noexcept override {
        return "the account is not pending";
    }
};

class AlreadyConnected : public GameServerError {
public:
    virtual int code() const override {
        return GameServerError::Code::ALREADY_CONNECTED;
    }

    virtual const char* what() const noexcept override {
        return "the account is already connected";
    }
};

} // namespace Server
} // namespace Dummy
