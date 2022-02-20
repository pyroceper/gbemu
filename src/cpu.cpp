#include "cpu.h"

CPU::CPU(const std::string &path)
{
    memory.load_ROM(path);
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
       
    fmt::print("PC: {0:#x}\n", reg_pc.reg);
    fmt::print("opcode: {0:#x}\n", opcode);


    switch(opcode) 
    {
        case 0x00: cycles += 4; break; //NOP

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

        //temp
        case 0x0A: // LD A, (BC)
            {
                cycles += 8;

                reg_af.hi = memory.read(reg_bc.reg);
            }
            break;
        case 0x1A: // LD A, (DE)
            {
                cycles += 8;

                reg_af.hi = memory.read(reg_de.reg);
            }
            break;
        case 0xFA: // LD A, (nn)
            {
                cycles += 16;

                uint8_t n1 = fetch_byte();
                uint8_t n2 = fetch_byte();
                uint16_t nn = (n2 << 8) | n1;

                reg_af.hi = memory.read(nn);
            }
            break;
        case 0x3E: // LD A, n
            {
                cycles += 8;

                uint8_t n = fetch_byte();

                reg_af.hi = n;

            }   
            break;
        
        case 0x4F: ld_rr(reg_bc.lo, reg_af.hi); break; // LD C, A
  
        case 0x57: ld_rr(reg_de.hi, reg_af.hi); break; // LD D, A
        case 0x5F: ld_rr(reg_de.lo, reg_af.hi); break; // LD E, A

        case 0x67: ld_rr(reg_hl.hi, reg_af.hi); break; // LD H, A
        case 0x6F: ld_rr(reg_hl.lo, reg_af.hi); break; // LD L, A
  
        
        //temp
        case 0x02: //LD (BC), A
            {
                cycles += 8;

                memory.write(reg_bc.reg, reg_af.hi);
            }
            break;
        case 0x12: //LD (DE), A
            {
                cycles += 8;

                memory.write(reg_de.reg, reg_af.hi);
            }
            break;
        case 0x77: //LD (HL), A
            {
                cycles += 8;

                memory.write(reg_hl.reg, reg_af.hi);
            }
            break;
        case 0xEA: //LD (nn), A
            { 
                cycles += 16;

                uint8_t n1 = fetch_byte();
                uint8_t n2 = fetch_byte();
                uint16_t nn = (n2 << 8) | n1;

                memory.write(nn, reg_af.hi);
            }
            break;

        
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

        //temp
        case 0x36: // LD (HL), n
            {
                cycles += 12;

                uint8_t n = fetch_byte();

                memory.write(reg_hl.reg, n);

            }
            break;


        case 0xF2: // LD A, (FF00 + C)
            {
                cycles += 8;

                reg_af.hi = memory.read(0xFF00 | reg_bc.lo);
            }
            break;
        case 0xE2: // LD (FF00 + C), A
            {
                cycles += 8;

                memory.write(0xFF00 | reg_bc.lo, reg_af.hi);
            }
            break;
    
        case 0x3A: // LD A, (HL-)
            {
                cycles += 8;

                reg_af.hi = memory.read(reg_hl.reg);
                reg_hl.reg--;

            }
            break;
        case 0x32: // LD (HL-), A
            {
                cycles += 8;
                
                memory.write(reg_hl.reg,  reg_af.hi);
                reg_hl.reg--;

            }
            break;
        
        case 0x2A: // LD A, (HL+)
            {
                cycles += 8;

                reg_af.hi = memory.read(reg_hl.reg);
                reg_hl.reg++;

            }
            break;
        case 0x22: // LD (HL+), A
            {
                cycles += 8;

                memory.write(reg_hl.reg, reg_af.hi);
                reg_hl.reg++;

            }
            break;

        case 0xE0: // LD (FF00 + n), A
            {
                cycles += 12;

                uint8_t n = fetch_byte();

                memory.write((0xFF00 | n), reg_af.hi);
            }
            break;
        case 0xF0: // LD A, (FF00 + n)
            {
                cycles += 12;

                uint8_t n = fetch_byte();

                reg_af.hi = memory.read((0xFF00 | n));
            }
            break;

        //8 bit ALU
        case 0x87: add_a_n(reg_af.hi); break; // ADD A, A

        case 0x80: add_a_n(reg_bc.hi); break; // ADD A, B
        case 0x81: add_a_n(reg_bc.lo); break; // ADD A, C
        case 0x82: add_a_n(reg_de.hi); break; // ADD A, D
        case 0x83: add_a_n(reg_de.lo); break; // ADD A, E
        case 0x84: add_a_n(reg_hl.hi); break; // ADD A, H
        case 0x85: add_a_n(reg_hl.lo); break; // ADD A, L
        case 0x86: // ADD A, (HL)
            { 
                increment_cycle(); 
                uint8_t n = memory.read(reg_hl.reg);
                add_a_n(n); 
            } 
            break; 
        case 0xC6: // ADD A, #
            {
                increment_cycle();

                uint8_t n = fetch_byte();

                add_a_n(n);
            }
            break;


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
    //read value
    uint8_t value {};
    reg_pc.reg++;
    value = memory.read(reg_pc.reg);

    reg = value;
}
//ld r1, r2
void CPU::ld_rr(uint8_t &reg1, uint8_t &reg2)
{
    cycles +=4 ;
    reg1 = reg2;
}
//ld r1, (HL)
void CPU::ld_r_hl(uint8_t &reg)
{
    cycles += 8;

    reg = memory.read(reg_hl.reg);
}
//temp
//ld (HL), r
void CPU::ld_hl_r(uint8_t &reg)
{
    cycles += 8;

    memory.write(reg_hl.reg, reg);
}

//8 bit ALU
// 8 bit addition
void CPU::add_a_n(uint8_t &n)
{
    cycles += 4;

    reset_flags();

    uint16_t result = reg_af.hi + n;

    if(result == 0)
        flag_z = true;
    
    flag_n = false;

    // set if carry from bit 3
    if( (reg_af.hi & 0b1111) + (n & 0b1111) > 0b1111)
        flag_h = true;

    // set if carry from bit 7
    if(result > 0b1111'1111)
        flag_c = true;

    reg_af.hi = (uint8_t)result;
}