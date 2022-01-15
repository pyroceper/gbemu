#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <cstdio>
#include <fmt/core.h>

#include "memory.h"

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

        Memory *memory = nullptr;

    private:
        Register reg_af;
        Register reg_bc;
        Register reg_de;
        Register reg_hl;
        
        uint8_t reg_flag;// Z N H C

        //instructions
        void ld_nn_n(uint8_t *reg);
        void ld_rr(uint8_t *reg1, uint8_t *reg2);

        void ld_r_hl(uint8_t *reg);
        void ld_hl_r(uint8_t *reg);

};


#endif