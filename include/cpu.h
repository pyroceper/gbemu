#ifndef CPU_H
#define CPU_H

#include <cstdint>

union Register
{
    struct 
    {
        uint8_t hi;
        uint8_t lo;
    };
    uint16_t reg;
};

class CPU
{
    public:
        void execute(uint8_t opcode);
};


#endif