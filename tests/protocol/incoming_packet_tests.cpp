#define BOOST_TEST_MODULE INCOMING_PACKET Unit Tests

#include <boost/test/included/unit_test.hpp>

#include "protocol/incoming_packet.hpp"
#include "utils.hpp"

BOOST_AUTO_TEST_CASE(parse_packet)
{
    const std::uint8_t buffer[] =
        "\x05\x00\x00\x00"  // size of "hello"
        "hello"             // the actual "hello" string
        "\x09\x00\x00\x00"  // size of "foobarbaz"
        "foobarbaz"         // the actual "foobarbaz" string
        "\x01"              // some uint8_t
        "\x32\x01"          // some uint16_t
        "\xef\xbe\xad\xde"; // some uint32_t

    Dummy::Protocol::IncomingPacket pkt(buffer);

    std::string firstString, secondString;
    uint8_t byte;
    uint16_t word;
    uint32_t dword;

    pkt >> firstString >> secondString >> byte >> word >> dword;

    BOOST_TEST(firstString == "hello");
    BOOST_TEST(secondString == "foobarbaz");
    BOOST_TEST(byte == 0x01);
    BOOST_TEST(word == 0x132);
    BOOST_TEST(dword == 0xdeadbeef);
}
