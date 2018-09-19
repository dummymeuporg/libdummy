#pragma once

#include <cstdint>

#include <openssl/sha.h>

namespace Dummy
{
namespace Crypto
{
    class SHA512
    {
    public:
        SHA512();
        ~SHA512();
        void update(const uint8_t*, size_t);
        void getDigest(uint8_t*);

    
    private:
        ::SHA512_CTX m_ctx;
    };
} // namespace Crypto
} // namespace Dummy
