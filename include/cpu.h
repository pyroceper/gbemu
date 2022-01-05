#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <cstdio>

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
        Register reg_pc;
        Register reg_sp;

        int cycles {};

    private:
        Register reg_af;
        Register reg_bc;
        Register reg_de;
        Register reg_hl;
        
        uint8_t reg_flag;// Z N H C

};


#endif