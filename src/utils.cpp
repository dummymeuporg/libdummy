#include <iomanip>
#include <iostream>
#include <sstream>

#include <boost/endian/conversion.hpp>

#include "utils.hpp"

std::string displayHash(const std::array<unsigned int, 5>& hash)
{
	std::ostringstream buf;
    for (int i = 0; i < 5; i++) {
		buf << std::hex << boost::endian::endian_reverse(hash[i]);
    }
    return buf.str();
}

void hexdump(const uint8_t* data, size_t size) {
    std::ostringstream buf;
    for (int i = 0; i < size; i++) {
        buf << std::setfill('0') << std::setw(2) << std::hex
            << static_cast<int>(data[i]);
    }

    std::cout << buf.str() << std::endl;
}
