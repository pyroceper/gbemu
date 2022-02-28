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

        bool halted;
        bool interrupt_enabled;

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

        //16 bit LD
        void ld_n_nn(uint16_t &reg);
        void ld_sp_hl();
        void ld_hl_sp();
        void ld_nn_sp();
        
        void sp_push(uint16_t &reg);
        void sp_pop(uint16_t &reg);


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

        void xor_byte(uint8_t &reg);
        void xor_hl();
        void xor_n();

        void cp_byte(uint8_t n);
        void cp_hl();
        void cp_n();

        void inc_reg(uint8_t &reg);
        void inc_hl();

        void dec_reg(uint8_t &reg);
        void dec_hl();

        //16 bit ALU
        void add_hl(uint16_t &reg);
        void add_sp();

        void inc_nn(uint16_t &reg);
        void dec_nn(uint16_t &reg);

        //misc
        void cpl();
        void ccf();
        void scf();
        void halt();
        void stop();
        void di();
        void ei();
        void daa();
        void swap(uint8_t &reg);
        void swap_hl();

        //rotates and shifts
        void rlc(uint8_t &reg);
        void rlc_hl();
        void rlca();
        void rla();
        void rl(uint8_t &reg);
        void rl_hl();
        
        void rra();
        void rrca();
        void rrc(uint8_t &reg);
        void rrc_hl();
        void rr(uint8_t &reg);
        void rr_hl();

        void sla(uint8_t &reg);
        void sla_hl();
        void sra(uint8_t &reg);
        void sra_hl();
        void srl(uint8_t &reg);
        void srl_hl();

        //bit operations
        void bit(uint8_t &reg, uint8_t b);
        void bit_hl(uint8_t b);
        void set(uint8_t &reg);
        void set_hl();
        void reset(uint8_t &reg);
        void reset_hl();

        //jumps
        void jp_nn();
        void jp_nz_nn();
        void jp_z_nn();
        void jp_nc_nn();
        void jp_c_nn();
        void jp_hl();
        void jr();
        void jr_nz();
        void jr_z();
        void jr_nc();
        void jr_c();

        //call
        void call_nn();
        void call_nz_nn();
        void call_z_nn();
        void call_nc_nn();
        void call_c_nn();

        //restart
        void rst_n(uint8_t n);

        //ret
        void ret();
        void ret_nz();
        void ret_z();
        void ret_nc();
        void ret_c();
        void reti();

        //helper
        uint8_t fetch_byte();
        void reset_flags();
        void increment_cycle();
        void jump();
        void jr_jump();
        void call();
        void ret_from_subroutine();
        
        void cb_opcodes();
};


#endif