#define BOOST_TEST_MODULE SHA512 Unit Tests
#include <cstring>

#include <boost/test/included/unit_test.hpp>

#include "crypto/sha512.hpp"


BOOST_AUTO_TEST_CASE(hash_string)
{
    std::uint8_t digest[SHA512_DIGEST_LENGTH];
    Dummy::Crypto::SHA512 hasher;
    hasher.update(reinterpret_cast<const std::uint8_t*>("foo"), 3);
    hasher.getDigest(digest);

    const std::uint8_t* target = reinterpret_cast<const std::uint8_t*>(
        "\xF7\xFB\xBA\x6E\x06\x36\xF8\x90\xE5\x6F\xBB\xF3\x28\x3E\x52\x4C"
        "\x6F\xA3\x20\x4A\xE2\x98\x38\x2D\x62\x47\x41\xD0\xDC\x66\x38\x32"
        "\x6E\x28\x2C\x41\xBE\x5E\x42\x54\xD8\x82\x07\x72\xC5\x51\x8A\x2C"
        "\x5A\x8C\x0C\x7F\x7E\xDA\x19\x59\x4A\x7E\xB5\x39\x45\x3E\x1E\xD7"
    );

    BOOST_TEST(std::memcmp(target, digest, SHA512_DIGEST_LENGTH) == 0);

}
