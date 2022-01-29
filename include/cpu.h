#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <cstdio>
#include <string>
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
        CPU(const std::string &path);
        void execute();
        Register reg_pc;
        Register reg_sp;

        int cycles {};

        Memory memory;

    private:
        Register reg_af;
        Register reg_bc;
        Register reg_de;
        Register reg_hl;
        
        uint8_t reg_flag;// Z N H C

        //instructions
        void ld_nn_n(uint8_t &reg);
        void ld_rr(uint8_t &reg1, uint8_t &reg2);

        void ld_r_hl(uint8_t &reg);
        void ld_hl_r(uint8_t &reg);

        //helper
        uint8_t fetch_byte();


};


#endif