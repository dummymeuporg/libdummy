#pragma once
#include <exception>

#include <openssl/pem.h>

namespace Dummy {

namespace Crypto {

class RSAKeyPairException : public std::exception {

};

class PEMFileError : public RSAKeyPairException {
    virtual const char* what() const throw() {
        return "error while loading the PEM file.";
    }
};

class KeyLoadingError : public RSAKeyPairException {
    virtual const char* what() const throw() {
        return "error while loading the key.";
    }
};

class RSAKeyPair {
    public:
        RSAKeyPair(const std::string&, const std::string&); // paths
        RSAKeyPair(EVP_PKEY*, EVP_PKEY*);
        virtual ~RSAKeyPair();

        EVP_PKEY* publicKey() {
            return m_publicKey;
        }

        EVP_PKEY* privateKey() {
            return m_privateKey;
        }

    private:
        void _loadKeysFromFiles(FILE*, FILE*);

        EVP_PKEY *m_publicKey, *m_privateKey;

};

} // namespace Crypto

} // namespace Dummy
