#pragma once

#include <array>
#include <string>

std::string displayHash(const std::array<unsigned int, 5>& hash);
void hexdump(const uint8_t* data, size_t size);
