#include <openssl/crypto.h>

#include "crypto/sha512.hpp"

namespace Dummy
{

namespace Crypto
{

SHA512::SHA512()
{
    ::SHA512_Init(&m_ctx);
}

SHA512::~SHA512()
{
    ::OPENSSL_cleanse(&m_ctx, sizeof(m_ctx));
}

void SHA512::update(const uint8_t* data, size_t len)
{
    ::SHA512_Update(&m_ctx, data, len);
}


void SHA512::getDigest(uint8_t* digest)
{
    ::SHA512_Final(digest, &m_ctx);
}


} // namespace Crypto

} // namespace Dummy
