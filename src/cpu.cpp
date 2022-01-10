#include "cpu.h"

void CPU::execute(uint8_t opcode)
{
    switch(opcode) 
    {
        case 0x06: // LD B, n
            {
                //immediate addressing
                reg_pc.reg++;
                ld_nn_n(&reg_bc.hi);
            }
            break;
        case 0x0E: // LD C, n
            {
                //immediate addressing
                reg_pc.reg++;
                ld_nn_n(&reg_bc.lo);
            }
            break;
        case 0x16: // LD D, n
            {
                //immediate addressing
                reg_pc.reg++;
                ld_nn_n(&reg_de.hi);
            }
            break;
        case 0x1E: // LD C, n
            {
                //immediate addressing
                reg_pc.reg++;
                ld_nn_n(&reg_bc.lo);
            }
            break;
        case 0x26: // LD H, n
            {
                //immediate addressing
                reg_pc.reg++;
                ld_nn_n(&reg_hl.hi);
            }
            break;
        case 0x2E: // LD L, n
            {
                //immediate addressing
                reg_pc.reg++;
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
            


        default: 
        {
            fmt::print("OPCODE UNKNOWN\n");
            reg_pc.reg++;
        }

    }

}

//instructions

//8 bit loads
// ld r, n
void CPU::ld_nn_n(uint8_t *reg)
{
    //read value
    uint8_t value {};
    value = memory->cartridge[reg_pc.reg];

    *reg = value;
    cycles += 8;
    reg_pc.reg++;
}
//ld r1, r2
void CPU::ld_rr(uint8_t *reg1, uint8_t *reg2)
{
    *reg1 = *reg2;
    cycles +=4 ;
    reg_pc.reg++;
}
