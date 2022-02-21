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
        
        //uint8_t reg_flag;// Z N H C
        bool flag_z; // zero
        bool flag_n; // subtraction
        bool flag_h; // half carry
        bool flag_c; // carry

        //instructions
        void ld_nn_n(uint8_t &reg);
        void ld_rr(uint8_t &reg1, uint8_t &reg2);
        void ld_a_rr(uint16_t &reg); // LD A, (reg)
        void ld_a_nn(); // LD A, (nn)
        void ld_a_n(); // LD A, n
        void ld_rr_a(uint16_t &reg); // LD (reg), A
        void ld_nn_a(); // LD (nn), A

        void ld_r_hl(uint8_t &reg);
        void ld_hl_r(uint8_t &reg);
        void ld_hl_n(); // LD (HL), n

        void ld_a_ffc(); // LD A, (FF00 + C)
        void ld_ffc_a(); // LD (FF00 + C), A

        void ld_a_ffn(); // LD A, (FF00 + n)
        void ld_ffn_a(); // LD (FF00 + n), A

        void ld_a_hl(bool increment); // LD A, (HL +/-)
        void ld_hl_a(bool increment); // LD (HL +/-), A


        //8 bit ALU
        void add_byte(uint8_t n, bool carry);
        void add_a_hl(bool carry);
        void add_a_n(bool carry);

        void sub_byte(uint8_t n, bool carry);
        void sub_r_hl(bool carry);
        void sub_r_n(bool carry);

        void and_byte(uint8_t &reg);
        void and_hl();
        void and_n();

        void or_byte(uint8_t &reg);
        void or_hl();
        void or_n();

        //helper
        uint8_t fetch_byte();
        void reset_flags();
        void increment_cycle();


};


#endif