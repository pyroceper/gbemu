#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include <fmt/core.h>

class Memory
{
    public:
        void load_ROM(const std::string &path);

        uint8_t rom[0x10000] {};

        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
};



#endif