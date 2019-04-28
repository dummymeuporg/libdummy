#include <iostream>
#include <string>

#include "crypto/rsa_keypair.hpp"


namespace Dummy {

namespace Crypto {

RSAKeyPair::RSAKeyPair(const std::string& publicKeyPath,
                       const std::string& privateKeyPath)
    : m_publicKey(nullptr), m_privateKey(nullptr)
{
    FILE *fpub = nullptr;
    FILE *fpriv = nullptr;

    if (nullptr == (fpub = ::fopen(publicKeyPath.c_str(), "rb")))
    {
        throw PEMFileError();
    }

    if(nullptr == (fpriv = ::fopen(privateKeyPath.c_str(), "rb")))
    {
        fclose(fpub);
        throw PEMFileError();
    }

    // Load the keys, close the files.
    _loadKeysFromFiles(fpub, fpriv);

}

RSAKeyPair::RSAKeyPair(EVP_PKEY* publicKey, EVP_PKEY* privateKey)
    : m_publicKey(publicKey), m_privateKey(privateKey)
{

}

RSAKeyPair::RSAKeyPair(FILE* fpub, FILE* fpriv)
    : m_publicKey(nullptr), m_privateKey(nullptr)
{
    _loadKeysFromFiles(fpub, fpriv);
}

RSAKeyPair::~RSAKeyPair() {
    EVP_PKEY_free(m_publicKey);
    EVP_PKEY_free(m_privateKey);
}

void RSAKeyPair::_loadKeysFromFiles(FILE* fpub, FILE* fpriv) {
    m_publicKey = PEM_read_PUBKEY(fpub, NULL, NULL, NULL);
    if (nullptr == m_publicKey) {
        throw KeyLoadingError();
    }

    m_privateKey = PEM_read_PrivateKey(fpriv, NULL, NULL, NULL);
    if (nullptr == m_privateKey) {
        EVP_PKEY_free(m_publicKey);
        throw KeyLoadingError();
    }
}

} // namespace Crypto

} // namespace Dummy
