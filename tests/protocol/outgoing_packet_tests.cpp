#define BOOST_TEST_MODULE OUTGOING_PACKET Unit Tests

#include <boost/test/included/unit_test.hpp>

#include "protocol/outgoing_packet.hpp"
#include "utils.hpp"

BOOST_AUTO_TEST_CASE(build_packet)
{
    Dummy::Protocol::OutgoingPacket pkt;
    std::uint16_t number = 3;

    pkt << number << std::string("hello");
    BOOST_TEST(pkt.dataSize() == 
        sizeof(std::uint16_t) + sizeof(std::uint32_t) + 5 /* "hello" */);
    BOOST_TEST(
        memcmp(
            pkt.buffer(),
            "\x0b\x00" // Internal size in little endian
            "\x03\x00" // number in little endian
            "\x05\x00\x00\x00" // Size of "hello" in little endian
            "hello", 
            pkt.size()
        ) == 0
    );
    BOOST_TEST(
        memcmp(
            pkt.data(),
            "\x03\x00" // number in little endian
            "\x05\x00\x00\x00" // Size of "hello" in little endian
            "hello", 
            pkt.dataSize()
        ) == 0
    );

}
