#include "cpu.h"

CPU::CPU(const std::string &path)
{
    memory.load_ROM(path);
}


void CPU::execute()
{
    //fetch
    uint8_t opcode = memory.rom[reg_pc.reg];
       
    fmt::print("PC: {0:#x}\n", reg_pc.reg);
    fmt::print("opcode: {0:#x}\n", opcode);

    //increment pc
    reg_pc.reg++;

    switch(opcode) 
    {
        case 0x00: // NOP
        {
            cycles += 4;
            // reg_pc.reg++;
        }
        break;

        case 0x06: // LD B, n
            {
                ld_nn_n(&reg_bc.hi);
            }
            break;
        case 0x0E: // LD C, n
            {
                ld_nn_n(&reg_bc.lo);
            }
            break;
        case 0x16: // LD D, n
            {
                ld_nn_n(&reg_de.hi);
            }
            break;
        case 0x1E: // LD C, n
            {
                ld_nn_n(&reg_bc.lo);
            }
            break;
        case 0x26: // LD H, n
            {
                ld_nn_n(&reg_hl.hi);
            }
            break;
        case 0x2E: // LD L, n
            {
                ld_nn_n(&reg_hl.lo);
            }
            break;



        case 0x7F: // LD A, A
            {
                ld_rr(&reg_af.hi, &reg_af.hi);
            }
            break;
        case 0x78: // LD A, B
            {
                ld_rr(&reg_af.hi, &reg_bc.hi);
            }
            break;
        case 0x79: // LD A, C
            {
                ld_rr(&reg_af.hi, &reg_bc.lo);
            }
            break;
        case 0x7A: // LD A, D
            {
                ld_rr(&reg_af.hi, &reg_de.hi);
            }
            break;
        case 0x7B: // LD A, E
            {
                ld_rr(&reg_af.hi, &reg_de.lo);
            }
            break;
        case 0x7C: // LD A, H
            {
                ld_rr(&reg_af.hi, &reg_hl.hi);
            }
            break;        
        case 0x7D: // LD A, L
            {
                ld_rr(&reg_af.hi, &reg_hl.lo);
            }
            break;
        case 0x40: // LD B, B
            {
                ld_rr(&reg_bc.hi, &reg_bc.hi);
            }
            break;
        case 0x41: // LD B, C
            {
                ld_rr(&reg_bc.hi, &reg_bc.lo);
            }
            break;
        case 0x42: // LD B, D
            {
                ld_rr(&reg_bc.hi, &reg_de.hi);
            }
            break;
        case 0x43: // LD B, E
            {
                ld_rr(&reg_bc.hi, &reg_de.lo);
            }
            break;
        case 0x44: // LD B, H
            {
                ld_rr(&reg_bc.hi, &reg_hl.hi);
            }
            break;
        case 0x45: // LD B, L
            {
                ld_rr(&reg_bc.hi, &reg_hl.lo);
            }
            break;
        case 0x47: // LD B, A
            {
                ld_rr(&reg_bc.hi, &reg_af.hi);
            }
            break;
        case 0x48: // LD C, B
            {
                ld_rr(&reg_bc.lo, &reg_bc.hi);
            }
            break; 
        case 0x49: // LD C, C
            {
                ld_rr(&reg_bc.lo, &reg_bc.lo);
            }
            break;
        case 0x4A: // LD C, D
            {
                ld_rr(&reg_bc.lo, &reg_de.hi);
            }
            break;
        case 0x4B: // LD C, E
            {
                ld_rr(&reg_bc.lo, &reg_de.lo);
            }
            break;
        case 0x4C: // LD C, H
            {
                ld_rr(&reg_bc.lo, &reg_hl.hi);
            }
            break;
        case 0x4D: // LD C, L
            {
                ld_rr(&reg_bc.lo, &reg_hl.lo);
            }
            break;
        case 0x50: // LD D, B
            {
                ld_rr(&reg_de.hi, &reg_bc.hi);
            }
            break;
        case 0x51: // LD D, C
            {
                ld_rr(&reg_de.hi, &reg_bc.lo);
            }
            break;
        case 0x52: // LD D, D
            {
                ld_rr(&reg_de.hi, &reg_de.hi);
            }
            break;
        case 0x53: // LD D, E
            {
                ld_rr(&reg_de.hi, &reg_de.lo);
            }
            break;
        case 0x54: // LD D, H
            {
                ld_rr(&reg_de.hi, &reg_hl.hi);
            }
            break;
        case 0x55: // LD D, L
            {
                ld_rr(&reg_de.hi, &reg_hl.lo);
            }
            break;
        case 0x58: // LD E, B
            {
                ld_rr(&reg_de.lo, &reg_bc.hi);
            }
            break;
        case 0x59: // LD E, C
            {
                ld_rr(&reg_de.lo, &reg_bc.lo);
            }
            break;
        case 0x5A: // LD E, D
            {
                ld_rr(&reg_de.lo, &reg_de.hi);
            }
            break;
        case 0x5B: // LD E, E
            {
                ld_rr(&reg_de.lo, &reg_de.lo);
            }
            break;
        case 0x5C: // LD E, H
            {
                ld_rr(&reg_de.lo, &reg_hl.hi);
            }
            break;
        case 0x5D: // LD E, L
            {
                ld_rr(&reg_de.lo, &reg_hl.lo);
            }
            break;  
        case 0x60: // LD H, B
            {
                ld_rr(&reg_hl.hi, &reg_bc.hi);
            }
            break;
        case 0x61: // LD H, C
            {
                ld_rr(&reg_hl.hi, &reg_bc.lo);
            }
            break;
        case 0x62: // LD H, D
            {
                ld_rr(&reg_hl.hi, &reg_de.hi);
            }
            break;
        case 0x63: // LD H, E
            {
                ld_rr(&reg_hl.hi, &reg_de.lo);
            }
            break;
        case 0x64: // LD H, H
            {
                ld_rr(&reg_hl.hi, &reg_hl.hi);
            }
            break;
        case 0x65: // LD H, L
            {
                ld_rr(&reg_hl.hi, &reg_hl.lo);
            }
            break;  
        case 0x68: // LD L, B
            {
                ld_rr(&reg_hl.lo, &reg_bc.hi);
            }
            break;
        case 0x69: // LD L, C
            {
                ld_rr(&reg_hl.lo, &reg_bc.lo);
            }
            break;
        case 0x6A: // LD L, D
            {
                ld_rr(&reg_hl.lo, &reg_de.hi);
            }
            break;
        case 0x6B: // LD L, E
            {
                ld_rr(&reg_hl.lo, &reg_de.lo);
            }
            break;
        case 0x6C: // LD L, H
            {
                ld_rr(&reg_hl.lo, &reg_hl.hi);
            }
            break;
        case 0x6D: // LD L, L
            {
                ld_rr(&reg_hl.lo, &reg_hl.lo);
            }
            break;  

        //temp
        case 0x0A: // LD A, (BC)
            {
                cycles += 8;

                reg_af.hi = memory.read(reg_bc.reg);
                // reg_pc.reg++;
            }
            break;
        case 0x1A: // LD A, (DE)
            {
                cycles += 8;

                reg_af.hi = memory.read(reg_de.reg);
                // reg_pc.reg++;
            }
            break;
        case 0xFA: // LD A, (nn)
            {
                cycles += 16;

                reg_pc.reg++;
                uint8_t n1 = memory.read(reg_pc.reg);
                reg_pc.reg++;
                uint8_t n2 = memory.read(reg_pc.reg);
                uint16_t nn = (n2 << 8) | n1;

                reg_af.hi = memory.read(nn);
                // reg_pc.reg++;
            }
            break;
        case 0x3E: // LD A, n
            {
                cycles += 8;

                reg_pc.reg++;
                uint8_t n = memory.read(reg_pc.reg);

                reg_af.hi = n;

                // reg_pc.reg++;
            }   
            break;
        
        case 0x4F: // LD C, A
            {
                ld_rr(&reg_bc.lo, &reg_af.hi);
            }
            break;
        case 0x57: // LD D, A
            {
                ld_rr(&reg_de.hi, &reg_af.hi);
            }
            break;
        case 0x5F: // LD E, A
            {
                ld_rr(&reg_de.lo, &reg_af.hi);
            }
            break;
        case 0x67: // LD H, A
            {
                ld_rr(&reg_hl.hi, &reg_af.hi);
            }
            break;
        case 0x6F:// LD L, A
            {
                ld_rr(&reg_hl.lo, &reg_af.hi);
            }
            break;
        
        //temp
        case 0x02: //LD (BC), A
            {
                cycles += 8;

                memory.write(reg_bc.reg, reg_af.hi);
                // reg_pc.reg++;
            }
            break;
        case 0x12: //LD (DE), A
            {
                cycles += 8;

                memory.write(reg_de.reg, reg_af.hi);
                // reg_pc.reg++;
            }
            break;
        case 0x77: //LD (HL), A
            {
                cycles += 8;

                memory.write(reg_hl.reg, reg_af.hi);
                // reg_pc.reg++;
            }
            break;
        case 0xEA: //LD (nn), A
            { 
                cycles += 16;

                reg_pc.reg++;
                uint8_t n1 = memory.read(reg_pc.reg);
                reg_pc.reg++;
                uint8_t n2 = memory.read(reg_pc.reg);
                uint16_t nn = (n2 << 8) | n1;

                memory.write(nn, reg_af.hi);
                // reg_pc.reg++;                
            }
            break;

        
        case 0x7E: // LD A, (HL)
            {
                ld_r_hl(&reg_af.hi);
            }
            break;
        case 0x46: // LD B, (HL)
            {
                ld_r_hl(&reg_bc.hi);
            }
            break;
        case 0x4E: // LD C, (HL)
            {
                ld_r_hl(&reg_bc.lo);
            }
            break;
        case 0x56: // LD D, (HL)
            {
                ld_r_hl(&reg_de.hi);
            }
            break;
        case 0x5E: // LD E, (HL)
            {
                ld_r_hl(&reg_de.lo);
            }
            break;
        case 0x66: // LD H, (HL)
            {
                ld_r_hl(&reg_hl.hi);
            }
            break;
        case 0x6E: // LD L, (HL)
            {
                ld_r_hl(&reg_hl.lo);
            }
            break;
        
        case 0x70: // LD (HL), B
            {
                ld_hl_r(&reg_bc.hi);
            }
            break;
        case 0x71: // LD (HL), C
            {
                ld_hl_r(&reg_bc.lo);
            }
            break;        
        case 0x72: // LD (HL), D
            {
                ld_hl_r(&reg_de.hi);
            }
            break;
        case 0x73: // LD (HL), E
            {
                ld_hl_r(&reg_de.lo);
            }
            break;
        case 0x74: // LD (HL), H
            {
                ld_hl_r(&reg_hl.hi);
            }
            break;
        case 0x75: // LD (HL), L
            {
                ld_hl_r(&reg_hl.lo);
            }
            break;
        //temp
        case 0x36: // LD (HL), n
            {
                cycles += 12;

                reg_pc.reg++;
                uint8_t n = memory.read(reg_pc.reg);

                memory.write(reg_hl.reg, n);

                // reg_pc.reg++;                
            }
            break;


        case 0xF2: // LD A, (FF00 + C)
            {
                cycles += 8;

                reg_af.hi = memory.read(0xFF00 | reg_bc.lo);
                // reg_pc.reg++;
            }
            break;
        case 0xE2: // LD (FF00 + C), A
            {
                cycles += 8;

                memory.write(0xFF00 | reg_bc.lo, reg_af.hi);
                // reg_pc.reg++;
            }
            break;
    
        case 0x3A: // LD A, (HL-)
            {
                cycles += 8;

                reg_af.hi = memory.read(reg_hl.reg);
                reg_hl.reg--;

                // reg_pc.reg++;
            }
            break;
        case 0x32: // LD (HL-), A
            {
                cycles += 8;
                
                memory.write(reg_hl.reg,  reg_af.hi);
                reg_hl.reg--;

                // reg_pc.reg++;
            }
            break;
        
        case 0x2A: // LD A, (HL+)
            {
                cycles += 8;

                reg_af.hi = memory.read(reg_hl.reg);
                reg_hl.reg++;

                // reg_pc.reg++;
            }
            break;
        case 0x22: // LD (HL+), A
            {
                cycles += 8;

                memory.write(reg_hl.reg, reg_af.hi);
                reg_hl.reg++;

                // reg_pc.reg++;
            }
            break;

        case 0xE0: // LD (FF00 + n), A
            {
                cycles += 12;

                reg_pc.reg++;
                uint8_t n = memory.read(reg_pc.reg);

                memory.write((0xFF00 | n), reg_af.hi);
                // reg_pc.reg++;
            }
            break;
        case 0xF0: // LD A, (FF00 + n)
            {
                cycles += 12;

                reg_pc.reg++;
                uint8_t n = memory.read(reg_pc.reg);

                reg_af.hi = memory.read((0xFF00 | n));
                // reg_pc.reg++;
            }
            break;


        default: 
        {
            fmt::print("OPCODE UNKNOWN\n");
            // reg_pc.reg++;
        }

    }

}

//instructions

//8 bit loads
// ld r, n
void CPU::ld_nn_n(uint8_t *reg)
{
    cycles += 8;
    //read value
    uint8_t value {};
    reg_pc.reg++;
    value = memory.rom[reg_pc.reg];

    *reg = value;
}
//ld r1, r2
void CPU::ld_rr(uint8_t *reg1, uint8_t *reg2)
{
    cycles +=4 ;
    *reg1 = *reg2;
}
//ld r1, (HL)
void CPU::ld_r_hl(uint8_t *reg)
{
    cycles += 8;

    *reg = memory.read(reg_hl.reg);
}
//temp
//ld (HL), r
void CPU::ld_hl_r(uint8_t *reg)
{
    cycles += 8;

    memory.write(reg_hl.reg, *reg);
}
