#include <exception>

namespace Dummy {

namespace Core {

class Error : public std::exception {

};

class WrongMagicNumber : public Error {
public:
    virtual const char* what() const noexcept override {
        return "the magic number is invalid.";
    }

};

} // namespace Dummy

} // namespace Core
