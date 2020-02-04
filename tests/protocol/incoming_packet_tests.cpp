#define BOOST_TEST_MODULE INCOMING_PACKET Unit Tests

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/test/included/unit_test.hpp>

#include "dummy/protocol/incoming_packet.hpp"
#include "dummy/utils/utils.hpp"

BOOST_AUTO_TEST_CASE(parse_packet)
{
    const uint8_t buffer[] =
        "\x05\x00\x00\x00"  // size of "hello"
        "hello"             // the actual "hello" string
        "\x09\x00\x00\x00"  // size of "foobarbaz"
        "foobarbaz"         // the actual "foobarbaz" string
        "\x01"              // some uint8_t
        "\x32\x01"          // some uint16_t
        "\xef\xbe\xad\xde" // some uint32_t
        "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f";

    Dummy::Protocol::IncomingPacket pkt(buffer, sizeof(buffer));

    std::string firstString, secondString;
    uint8_t byte;
    uint16_t word;
    uint32_t dword;
    std::array<uint8_t, 16> array;
    boost::uuids::uuid uuid;
    boost::uuids::string_generator gen;

    pkt >> firstString >> secondString >> byte >> word >> dword
        >> array;

    std::copy(array.begin(), array.end(), uuid.data);

    BOOST_TEST(firstString == "hello");
    BOOST_TEST(secondString == "foobarbaz");
    BOOST_TEST(byte == 0x01);
    BOOST_TEST(word == 0x132);
    BOOST_TEST(dword == 0xdeadbeef);
    BOOST_TEST(
        uuid == gen("00010203-0405-0607-0809-0a0b0c0d0e0f")
    );
}
