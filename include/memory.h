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
        Memory(const std::string &path);
        void load_ROM(const std::string &path);

        std::vector<uint8_t> cartridge;
        bool rom_load_fail = false;
};



#endif