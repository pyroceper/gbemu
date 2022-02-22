#include "cpu.h"

CPU::CPU(const std::string &path)
{
    memory.load_ROM(path);
    reset_flags();
}

uint8_t CPU::fetch_byte() 
{
    uint8_t byte = memory.read(reg_pc.reg);
    reg_pc.reg++;
    
    return byte;
}

void CPU::reset_flags() 
{
    flag_z = flag_n = flag_h = flag_c = false;
}

void CPU::increment_cycle() 
{
    cycles += 4;
}

void CPU::execute()
{
    //fetch
    uint8_t opcode = fetch_byte();
       
    fmt::print("PC: {0:#x}\n", reg_pc.reg - 1);
    fmt::print("opcode: {0:#x}\n", opcode);


    switch(opcode) 
    {
        case 0x00: increment_cycle(); break; //NOP

        case 0x06: ld_nn_n(reg_bc.hi); break; // LD B, n
        case 0x0E: ld_nn_n(reg_bc.lo); break; // LD C, n
        case 0x1E: ld_nn_n(reg_de.lo); break; // LD E, n

        case 0x16: ld_nn_n(reg_de.hi); break; // LD D, n
        case 0x26: ld_nn_n(reg_hl.hi); break; // LD H, n
        case 0x2E: ld_nn_n(reg_hl.lo); break; // LD L, n

        case 0x7F: ld_rr(reg_af.hi, reg_af.hi); break; // LD A, A
        case 0x78: ld_rr(reg_af.hi, reg_bc.hi); break; // LD A, B
        case 0x79: ld_rr(reg_af.hi, reg_bc.lo); break; // LD A, C
        case 0x7A: ld_rr(reg_af.hi, reg_de.hi); break; // LD A, D
        case 0x7B: ld_rr(reg_af.hi, reg_de.lo); break; // LD A, E
        case 0x7C: ld_rr(reg_af.hi, reg_hl.hi); break; // LD A, H
        case 0x7D: ld_rr(reg_af.hi, reg_hl.lo); break; // LD A, L

        case 0x40: ld_rr(reg_bc.hi, reg_bc.hi); break; // LD B, B
        case 0x41: ld_rr(reg_bc.hi, reg_bc.lo); break; // LD B, C
        case 0x42: ld_rr(reg_bc.hi, reg_de.hi); break; // LD B, D
        case 0x43: ld_rr(reg_bc.hi, reg_de.lo); break; // LD B, E
        case 0x44: ld_rr(reg_bc.hi, reg_hl.hi); break; // LD B, H
        case 0x45: ld_rr(reg_bc.hi, reg_hl.lo); break; // LD B, L

        case 0x47: ld_rr(reg_bc.hi, reg_af.hi); break; // LD B, A
        case 0x48: ld_rr(reg_bc.lo, reg_bc.hi); break; // LD C, B
        case 0x49: ld_rr(reg_bc.lo, reg_bc.lo); break; // LD C, C

        case 0x4A: ld_rr(reg_bc.lo, reg_de.hi); break; // LD C, D
        case 0x4B: ld_rr(reg_bc.lo, reg_de.lo); break; // LD C, E
        case 0x4C: ld_rr(reg_bc.lo, reg_hl.hi); break; // LD C, H
        case 0x4D: ld_rr(reg_bc.lo, reg_hl.lo); break; // LD C, L
  
        case 0x50: ld_rr(reg_de.hi, reg_bc.hi); break; // LD D, B
        case 0x51: ld_rr(reg_de.hi, reg_bc.lo); break; // LD D, C
        case 0x52: ld_rr(reg_de.hi, reg_de.hi); break; // LD D, D
        case 0x53: ld_rr(reg_de.hi, reg_de.lo); break; // LD D, E
        case 0x54: ld_rr(reg_de.hi, reg_hl.hi); break; // LD D, H
        case 0x55: ld_rr(reg_de.hi, reg_hl.lo); break; // LD D, L

        case 0x58: ld_rr(reg_de.lo, reg_bc.hi); break; // LD E, B
        case 0x59: ld_rr(reg_de.lo, reg_bc.lo); break; // LD E, C    
        case 0x5A: ld_rr(reg_de.lo, reg_de.hi); break; // LD E, D
        case 0x5B: ld_rr(reg_de.lo, reg_de.lo); break; // LD E, E
        case 0x5C: ld_rr(reg_de.lo, reg_hl.hi); break; // LD E, H
        case 0x5D: ld_rr(reg_de.lo, reg_hl.lo); break; // LD E, L

        case 0x60: ld_rr(reg_hl.hi, reg_bc.hi); break; // LD H, B
        case 0x61: ld_rr(reg_hl.hi, reg_bc.lo); break; // LD H, C
        case 0x62: ld_rr(reg_hl.hi, reg_de.hi); break; // LD H, D
        case 0x63: ld_rr(reg_hl.hi, reg_de.lo); break; // LD H, E
        case 0x64: ld_rr(reg_hl.hi, reg_hl.hi); break; // LD H, H
        case 0x65: ld_rr(reg_hl.hi, reg_hl.lo); break; // LD H, L

        case 0x68: ld_rr(reg_hl.lo, reg_bc.hi); break; // LD L, B
        case 0x69: ld_rr(reg_hl.lo, reg_bc.lo); break; // LD L, C
        case 0x6A: ld_rr(reg_hl.lo, reg_de.hi); break; // LD L, D
        case 0x6B: ld_rr(reg_hl.lo, reg_de.lo); break; // LD L, E
        case 0x6C: ld_rr(reg_hl.lo, reg_hl.hi); break; // LD L, H
        case 0x6D: ld_rr(reg_hl.lo, reg_hl.lo); break; // LD L, L

        case 0x0A: ld_a_rr(reg_bc.reg); break; // LD A, (BC)
        case 0x1A: ld_a_rr(reg_de.reg); break; // LD A, (DE)
 
        case 0xFA: ld_a_nn(); break; // LD A, (nn)

        case 0x3E: ld_a_n(); break; // LD A, n
        
        case 0x4F: ld_rr(reg_bc.lo, reg_af.hi); break; // LD C, A
        case 0x57: ld_rr(reg_de.hi, reg_af.hi); break; // LD D, A
        case 0x5F: ld_rr(reg_de.lo, reg_af.hi); break; // LD E, A
        case 0x67: ld_rr(reg_hl.hi, reg_af.hi); break; // LD H, A
        case 0x6F: ld_rr(reg_hl.lo, reg_af.hi); break; // LD L, A
  
        case 0x02: ld_rr_a(reg_bc.reg); break; //LD (BC), A
        case 0x12: ld_rr_a(reg_de.reg); break; //LD (DE), A
        case 0x77: ld_rr_a(reg_hl.reg); break; //LD (HL), A

        case 0xEA: ld_nn_a(); break; //LD (nn), A
        
        case 0x7E: ld_r_hl(reg_af.hi); break; // LD A, (HL)
        case 0x46: ld_r_hl(reg_bc.hi); break; // LD B, (HL)
        case 0x4E: ld_r_hl(reg_bc.lo); break; // LD C, (HL)
        case 0x56: ld_r_hl(reg_de.hi); break; // LD D, (HL)
        case 0x5E: ld_r_hl(reg_de.lo); break; // LD E, (HL)
        case 0x66: ld_r_hl(reg_hl.hi); break; // LD H, (HL)
        case 0x6E: ld_r_hl(reg_hl.lo); break; // LD L, (HL)
     
        case 0x70: ld_hl_r(reg_bc.hi); break; // LD (HL), B
        case 0x71: ld_hl_r(reg_bc.lo); break; // LD (HL), C        
        case 0x72: ld_hl_r(reg_de.hi); break; // LD (HL), D
        case 0x73: ld_hl_r(reg_de.lo); break; // LD (HL), E
        case 0x74: ld_hl_r(reg_hl.hi); break; // LD (HL), H
        case 0x75: ld_hl_r(reg_hl.lo); break; // LD (HL), L

        case 0x36: ld_hl_n(); break; // LD (HL), n

        case 0xF2: ld_a_ffc(); break; // LD A, (FF00 + C)
  
        case 0xE2: ld_ffc_a(); break; // LD (FF00 + C), A
    
        case 0x3A: ld_a_hl(false); break; // LD A, (HL-)
        case 0x2A: ld_a_hl(true); break; // LD A, (HL+)


        case 0x32: ld_hl_a(false); break; // LD (HL-), A        
        case 0x22: ld_hl_a(true); break; // LD (HL+), A

        case 0xE0: ld_ffn_a(); break; // LD (FF00 + n), A
        case 0xF0: ld_a_ffn(); break; // LD A, (FF00 + n)

        //8 bit ALU
        case 0x87: add_byte(reg_af.hi, false); break; // ADD A, A

        case 0x80: add_byte(reg_bc.hi, false); break; // ADD A, B
        case 0x81: add_byte(reg_bc.lo, false); break; // ADD A, C
        case 0x82: add_byte(reg_de.hi, false); break; // ADD A, D
        case 0x83: add_byte(reg_de.lo, false); break; // ADD A, E
        case 0x84: add_byte(reg_hl.hi, false); break; // ADD A, H
        case 0x85: add_byte(reg_hl.lo, false); break; // ADD A, L
        case 0x86: add_a_hl(false); break; // ADD A, (HL)
        case 0xC6: add_a_n(false); break; // ADD A, #

        case 0x8F: add_byte(reg_af.hi, true); break; // ADC A, A

        case 0x88: add_byte(reg_bc.hi, true); break; // ADC A, B
        case 0x89: add_byte(reg_bc.lo, true); break; // ADC A, C
        case 0x8A: add_byte(reg_de.hi, true); break; // ADC A, D
        case 0x8B: add_byte(reg_de.lo, true); break; // ADC A, E
        case 0x8C: add_byte(reg_hl.hi, true); break; // ADC A, H
        case 0x8D: add_byte(reg_hl.lo, true); break; // ADC A, L
        case 0x8E: add_a_hl(true); break; // ADC A, (HL)
        case 0xCE: add_a_n(true); break; // ADC A, #

        case 0x97: sub_byte(reg_af.hi, false); break; // SUB A, A
        
        case 0x90: sub_byte(reg_bc.hi, false); break; // SUB A, B
        case 0x91: sub_byte(reg_bc.lo, false); break; // SUB A, C
        case 0x92: sub_byte(reg_de.hi, false); break; // SUB A, D
        case 0x93: sub_byte(reg_de.lo, false); break; // SUB A, E
        case 0x94: sub_byte(reg_hl.hi, false); break; // SUB A, H
        case 0x95: sub_byte(reg_hl.lo, false); break; // SUB A, L
        case 0x96: sub_r_hl(false); break; // SUB A, (HL)
        case 0xD6: sub_r_n(false); break; // SUB A, #

        case 0x9F: sub_byte(reg_af.hi, true); break; // SBC A, A
        
        case 0x98: sub_byte(reg_bc.hi, true); break; // SBC A, B
        case 0x99: sub_byte(reg_bc.lo, true); break; // SBC A, C
        case 0x9A: sub_byte(reg_de.hi, true); break; // SBC A, D
        case 0x9B: sub_byte(reg_de.lo, true); break; // SBC A, E
        case 0x9C: sub_byte(reg_hl.hi, true); break; // SBC A, H
        case 0x9D: sub_byte(reg_hl.lo, true); break; // SBC A, L
        case 0x9E: sub_r_hl(true); break; // SBC A, (HL)        
     
        case 0xA7: and_byte(reg_af.hi); break; // AND A, A

        case 0xA0: and_byte(reg_bc.hi); break; // AND A, B
        case 0xA1: and_byte(reg_bc.lo); break; // AND A, C
        case 0xA2: and_byte(reg_de.hi); break; // AND A, D
        case 0xA3: and_byte(reg_de.lo); break; // AND A, E
        case 0xA4: and_byte(reg_hl.hi); break; // AND A, H
        case 0xA5: and_byte(reg_hl.lo); break; // AND A, L
        case 0xA6: and_hl(); break; // AND A, (HL)
        case 0xE6: and_n(); break; // AND A, #

        case 0xB7: or_byte(reg_af.hi); break; // OR A, A
        
        case 0xB0: or_byte(reg_bc.hi); break; // OR A, B
        case 0xB1: or_byte(reg_bc.lo); break; // OR A, C
        case 0xB2: or_byte(reg_de.hi); break; // OR A, D
        case 0xB3: or_byte(reg_de.lo); break; // OR A, E
        case 0xB4: or_byte(reg_hl.hi); break; // OR A, H
        case 0xB5: or_byte(reg_hl.lo); break; // OR A, L
        case 0xB6: or_hl(); break; // OR A, (HL)
        case 0xF6: or_n(); break; // OR A, #

        case 0xAF: xor_byte(reg_af.hi); break; // XOR A, A
        
        case 0xA8: xor_byte(reg_bc.hi); break; // XOR A, B
        case 0xA9: xor_byte(reg_bc.lo); break; // XOR A, C
        case 0xAA: xor_byte(reg_de.hi); break; // XOR A, D
        case 0xAB: xor_byte(reg_de.lo); break; // XOR A, E
        case 0xAC: xor_byte(reg_hl.hi); break; // XOR A, H
        case 0xAD: xor_byte(reg_hl.lo); break; // XOR A, L
        case 0xAE: xor_hl(); break; // XOR A, (HL)
        case 0xEE: xor_n(); break; // XOR A, #

        case 0xBF: cp_byte(reg_af.hi); break; // CP A
        case 0xB8: cp_byte(reg_bc.hi); break; // CP B
        case 0xB9: cp_byte(reg_bc.lo); break; // CP C
        case 0xBA: cp_byte(reg_de.hi); break; // CP D
        case 0xBB: cp_byte(reg_de.lo); break; // CP E
        case 0xBC: cp_byte(reg_hl.hi); break; // CP H
        case 0xBD: cp_byte(reg_hl.lo); break; // CP L
        case 0xBE: cp_hl(); break; // CP (HL)
        case 0xFE: cp_n(); break; // CP #

        case 0x3C: inc_reg(reg_af.hi); break; // INC A
        case 0x04: inc_reg(reg_bc.hi); break; // INC B
        case 0x0C: inc_reg(reg_bc.lo); break; // INC C
        case 0x14: inc_reg(reg_de.hi); break; // INC D
        case 0x1C: inc_reg(reg_de.lo); break; // INC E
        case 0x24: inc_reg(reg_hl.hi); break; // INC H
        case 0x2C: inc_reg(reg_hl.lo); break; // INC L
        case 0x34: inc_hl(); break; // INC (HL)

        case 0x3D: dec_reg(reg_af.hi); break; // DEC A
        case 0x05: dec_reg(reg_bc.hi); break; // DEC B
        case 0x0D: dec_reg(reg_bc.lo); break; // DEC C
        case 0x15: dec_reg(reg_de.hi); break; // DEC D
        case 0x1D: dec_reg(reg_de.lo); break; // DEC E
        case 0x25: dec_reg(reg_hl.hi); break; // DEC H
        case 0x2D: dec_reg(reg_hl.lo); break; // DEC L
        case 0x35: dec_hl(); break; // DEC (HL)


        default: 
        {
            fmt::print("OPCODE UNKNOWN\n");
        }

    }

}

//instructions

//8 bit loads
// ld r, n
void CPU::ld_nn_n(uint8_t &reg)
{
    cycles += 8;

    reg = fetch_byte();
}
//ld r1, r2
void CPU::ld_rr(uint8_t &reg1, uint8_t &reg2)
{
    cycles += 4;
    reg1 = reg2;
}
//ld r1, (HL)
void CPU::ld_r_hl(uint8_t &reg)
{
    cycles += 8;

    reg = memory.read(reg_hl.reg);
}
//ld A, (rr)
void CPU::ld_a_rr(uint16_t &reg)
{
    cycles += 8;
    reg_af.hi = memory.read(reg);
}
//ld A, (nn)
void CPU::ld_a_nn()
{
    cycles += 16;

    uint8_t n1 = fetch_byte();
    uint8_t n2 = fetch_byte();
    uint16_t nn = (n2 << 8) | n1;

    reg_af.hi = memory.read(nn);
}
//ld A, n
void CPU::ld_a_n()
{
    cycles += 8;
    uint8_t n = fetch_byte();
    reg_af.hi = n;
}
//ld (reg), A
void CPU::ld_rr_a(uint16_t &reg)
{               
    cycles += 8;
    memory.write(reg, reg_af.hi);
}
//ld (nn), A
void CPU::ld_nn_a()
{
    cycles += 16;

    uint8_t n1 = fetch_byte();
    uint8_t n2 = fetch_byte();
    uint16_t nn = (n2 << 8) | n1;

    memory.write(nn, reg_af.hi);
}

//ld (HL), r
void CPU::ld_hl_r(uint8_t &reg)
{
    cycles += 8;

    memory.write(reg_hl.reg, reg);
}
//ld (HL), n
void CPU::ld_hl_n()
{
    cycles += 12;

    uint8_t n = fetch_byte();

    memory.write(reg_hl.reg, n);
}
//ld A, (FF00 + C)
void CPU::ld_a_ffc()
{
    cycles += 8;

    reg_af.hi = memory.read(0xFF00 | reg_bc.lo);
}
//ld (FF00 + C), A
void CPU::ld_ffc_a()
{
    cycles += 8;

    memory.write(0xFF00 | reg_bc.lo, reg_af.hi);
}
//ld A, (FF00 + n)
void CPU::ld_a_ffn()
{
    cycles += 12;

    uint8_t n = fetch_byte();

    reg_af.hi = memory.read((0xFF00 | n));
}
//ld (FF00 + n), A
void CPU::ld_ffn_a()
{
    cycles += 12;

    uint8_t n = fetch_byte();

    memory.write((0xFF00 | n), reg_af.hi);
}

//ld A, (HL +/-)
void CPU::ld_a_hl(bool increment)
{
    cycles += 8;

    reg_af.hi = memory.read(reg_hl.reg);
    
    reg_hl.reg = (increment) ? reg_hl.reg++ : reg_hl.reg--;
}
//ld (HL +/-), A
void CPU::ld_hl_a(bool increment)
{
    cycles += 8;
                
    memory.write(reg_hl.reg,  reg_af.hi);

    reg_hl.reg = (increment) ? reg_hl.reg++ : reg_hl.reg--;
}


//8 bit ALU
// 8 bit addition
void CPU::add_byte(uint8_t n, bool carry)
{
    increment_cycle();

    reset_flags();

    uint16_t result = reg_af.hi + n + carry;
    
    flag_n = false;

    // set if carry from bit 3
    flag_h = ( (reg_af.hi & 0b1111) + (n & 0b1111) + carry > 0b1111 );

    // set if carry from bit 7
    flag_c = (result > 0b1111'1111);

    reg_af.hi = result;

    flag_z = (reg_af.hi == 0);
}

void CPU::add_a_hl(bool carry)
{
    increment_cycle(); 
    uint8_t n = memory.read(reg_hl.reg);
    add_byte(n, carry); 
}

void CPU::add_a_n(bool carry)
{
    increment_cycle();
    uint8_t n = fetch_byte();
    add_byte(n, carry);
}

void CPU::sub_byte(uint8_t n, bool carry)
{
    increment_cycle();

    reset_flags();

    flag_n = true;

    // set if no borrow from bit 4
    flag_h = ( (reg_af.hi & 0b1111) - ((n & 0b1111) + carry) < 0 );

    // set if no borrow
    flag_c = (reg_af.hi < n + carry);

    reg_af.hi = reg_af.hi - (n + carry);

    flag_z = (reg_af.hi == 0);
}

void CPU::sub_r_hl(bool carry)
{
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    sub_byte(n, carry);
}

void CPU::sub_r_n(bool carry)
{
    increment_cycle();
    uint8_t n = fetch_byte();
    sub_byte(n, carry);
}

void CPU::and_byte(uint8_t &reg)
{
    increment_cycle();
    
    reset_flags();

    reg_af.hi = reg_af.hi & reg;

    flag_z = (reg_af.hi == 0);
    flag_n = false;
    flag_h = true;
    flag_c = false;
}

void CPU::and_hl()
{
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    and_byte(n);
}

void CPU::and_n()
{
    increment_cycle();
    uint8_t n = fetch_byte();
    and_byte(n);
}

void CPU::or_byte(uint8_t &reg)
{
    increment_cycle();
    
    reset_flags();

    reg_af.hi = reg_af.hi | reg;

    flag_z = (reg_af.hi == 0);
}

void CPU::or_hl()
{
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    or_byte(n);
}

void CPU::or_n()
{
    increment_cycle();
    uint8_t n = fetch_byte();
    or_byte(n);
}

void CPU::xor_byte(uint8_t &reg)
{
    increment_cycle();

    reset_flags();

    reg_af.hi = reg_af.hi ^ reg;

    flag_z = (reg_af.hi == 0);
}

void CPU::xor_hl()
{
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    xor_byte(n);
}

void CPU::xor_n()
{
    increment_cycle();
    uint8_t n = fetch_byte();
    xor_byte(n);
}

void CPU::cp_byte(uint8_t n)
{
    increment_cycle();

    reset_flags();

    uint8_t result = reg_af.hi - n;

    flag_n = true;

    // set if no borrow from bit 4
    flag_h = ( (reg_af.hi & 0b1111) - (n & 0b1111) < 0 );

    // set if no borrow
    flag_c = (reg_af.hi < n);

    flag_z = (result == 0);   
}

void CPU::cp_hl()
{
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    cp_byte(n);
}

void CPU::cp_n()
{
    increment_cycle();
    uint8_t n = fetch_byte();
    cp_byte(n);
}

void CPU::inc_reg(uint8_t &reg)
{
    increment_cycle();

    reg++;

    flag_z = (reg == 0);
    
    flag_n = false;
    
    flag_h = ( (reg & 0b1111) == 0 ); // if last 4 bits are 0, then there was halfcarry
}

void CPU::inc_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    inc_reg(n);
    memory.write(reg_hl.reg, n);
}

void CPU::dec_reg(uint8_t &reg)
{
    increment_cycle();

    reg--;

    flag_z = (reg == 0);
   
    flag_n = true;
   
    flag_h = ((reg & 0b1111) == 0b1111); // if last 4 bits are 1s, then there's no halfcarry
}

void CPU::dec_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    dec_reg(n);
    memory.write(reg_hl.reg, n);
}