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

        //16 bit LD
        case 0x01: ld_n_nn(reg_bc.reg); break; // LD BC, nn
        case 0x11: ld_n_nn(reg_de.reg); break; // LD DE, nn
        case 0x21: ld_n_nn(reg_hl.reg); break; // LD HL, nn
        case 0x31: ld_n_nn(reg_sp.reg); break; // LD SP, nn

        case 0xF9: ld_sp_hl(); break; // LD SP, HL
        case 0xF8: ld_hl_sp(); break; // LD HL, SP + n

        case 0x08: ld_nn_sp(); break; // LD (nn), SP

        case 0xF5: sp_push(reg_af.reg); break; // PUSH AF
        case 0xC5: sp_push(reg_bc.reg); break; // PUSH BC
        case 0xD5: sp_push(reg_de.reg); break; // PUSH DE
        case 0xE5: sp_push(reg_hl.reg); break; // PUSH HL

        case 0xF1: sp_pop(reg_af.reg); break; // POP AF
        case 0xC1: sp_pop(reg_bc.reg); break; // POP BC
        case 0xD1: sp_pop(reg_de.reg); break; // POP DE
        case 0xE1: sp_pop(reg_hl.reg); break; // POP HL

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

        //16 bit ALU
        case 0x09: add_hl(reg_bc.reg); break; // ADD HL, BC
        case 0x19: add_hl(reg_de.reg); break; // ADD HL, DE
        case 0x29: add_hl(reg_hl.reg); break; // ADD HL, HL
        case 0x39: add_hl(reg_sp.reg); break; // ADD HL, SP

        case 0xE8: add_sp(); break; // ADD SP, n

        case 0x03: inc_nn(reg_bc.reg); break; // INC BC
        case 0x13: inc_nn(reg_de.reg); break; // INC DE
        case 0x23: inc_nn(reg_hl.reg); break; // INC HL
        case 0x33: inc_nn(reg_sp.reg); break; // INC SP

        case 0x0B: dec_nn(reg_bc.reg); break; // DEC BC
        case 0x1B: dec_nn(reg_de.reg); break; // DEC DE
        case 0x2B: dec_nn(reg_hl.reg); break; // DEC HL
        case 0x3B: dec_nn(reg_sp.reg); break; // DEC SP

        //misc
        case 0x2F: cpl(); break; // CPL
        case 0x3F: ccf(); break; // CCF
        case 0x37: scf(); break; // SCF
        case 0x76: halt(); break; // HALT
        case 0x10: stop(); break; // STOP
        case 0xF3: di(); break; // DI
        case 0xFB: ei(); break; // EI
        case 0x27: daa(); break; // DAA

        //rotate and shift
        case 0x07: rlca(); break; // RLCA
        case 0x17: rla(); break; // RLA
        case 0x1F: rra(); break; // RRA
        case 0x0F: rrca(); break; // RRCA

        //jumps
        case 0xC3: jp_nn(); break; // JP nn
        case 0xC2: jp_nz_nn(); break; // JP NZ, nn
        case 0xCA: jp_z_nn(); break; // JP Z, nn
        case 0xD2: jp_nc_nn(); break; // JP NC, nn
        case 0xDA: jp_c_nn(); break; // JP C, nn
        case 0xE9: jp_hl(); break; // JP HL
        case 0x18: jr(); break; // JR n
        case 0x20: jr_nz(); break; // JR NZ, n
        case 0x28: jr_z(); break; // JR Z, n
        case 0x30: jr_nc(); break; // JR NC, n
        case 0x38: jr_c(); break; // JR C, n

        //call
        case 0xCD: call_nn(); break; // CALL nn
        case 0xC4: call_nz_nn(); break; // CALL NZ, nn
        case 0xCC: call_z_nn(); break; // CALL Z, nn
        case 0xD4: call_nc_nn(); break; // CALL NC, nn
        case 0xDC: call_c_nn(); break; // CALL C, nn

        //restart
        case 0xC7: rst_n(0x00); // RST 00H
        case 0xCF: rst_n(0x08); // RST 08H
        case 0xD7: rst_n(0x10); // RST 10H
        case 0xDF: rst_n(0x18); // RST 18H
        case 0xE7: rst_n(0x20); // RST 20H
        case 0xEF: rst_n(0x28); // RST 28H
        case 0xF7: rst_n(0x30); // RST 30H
        case 0xFF: rst_n(0x38); // RST 38H

        //return
        case 0xC9: ret(); // RET
        case 0xC0: ret_nz(); // RET NZ
        case 0xC8: ret_z(); // RET Z
        case 0xD0: ret_nc(); // RET NC
        case 0xD8: ret_c(); // RET C
        case 0xD9: reti(); // RETI

        //prefix cb
        case 0xCB: cb_opcodes(); break;

        default: 
        {
            fmt::print("OPCODE UNKNOWN\n");
        }

    }

}

void CPU::cb_opcodes()
{
    //fetch
    uint8_t opcode = fetch_byte();
       
    fmt::print("CB opcode: {0:#x}\n", opcode);
    
    switch(opcode)
    {
        //SWAP
        case 0x37: swap(reg_af.hi); break; // SWAP A
        case 0x30: swap(reg_bc.hi); break; // SWAP B
        case 0x31: swap(reg_bc.lo); break; // SWAP C
        case 0x32: swap(reg_de.hi); break; // SWAP D
        case 0x33: swap(reg_de.lo); break; // SWAP E
        case 0x34: swap(reg_hl.hi); break; // SWAP H
        case 0x35: swap(reg_hl.lo); break; // SWAP L
        case 0x36: swap_hl(); break; // SWAP (HL)

        //rotate and shift
        case 0x07: rlc(reg_af.hi); break; // RLC A
        case 0x00: rlc(reg_bc.hi); break; // RLC B
        case 0x01: rlc(reg_bc.lo); break; // RLC C
        case 0x02: rlc(reg_de.hi); break; // RLC D
        case 0x03: rlc(reg_de.lo); break; // RLC E
        case 0x04: rlc(reg_hl.hi); break; // RLC H
        case 0x05: rlc(reg_hl.lo); break; // RLC L
        case 0x06: rlc_hl(); break; // RLC (HL)

        case 0x17: rl(reg_af.hi); break; // RL A
        case 0x10: rl(reg_bc.hi); break; // RL B
        case 0x11: rl(reg_bc.lo); break; // RL C
        case 0x12: rl(reg_de.hi); break; // RL D
        case 0x13: rl(reg_de.lo); break; // RL E
        case 0x14: rl(reg_hl.hi); break; // RL H
        case 0x15: rl(reg_hl.lo); break; // RL L
        case 0x16: rl_hl(); break; // RL (HL)

        case 0x0F: rrc(reg_af.hi); break; // RRC A
        case 0x08: rrc(reg_bc.hi); break; // RRC B
        case 0x09: rrc(reg_bc.lo); break; // RRC C
        case 0x0A: rrc(reg_de.hi); break; // RRC D
        case 0x0B: rrc(reg_de.lo); break; // RRC E
        case 0x0C: rrc(reg_hl.hi); break; // RRC H
        case 0x0D: rrc(reg_hl.lo); break; // RRC L
        case 0x0E: rrc_hl(); break; // RRC (HL)

        case 0x1F: rr(reg_af.hi); break; // RR A
        case 0x18: rr(reg_bc.hi); break; // RR B
        case 0x19: rr(reg_bc.lo); break; // RR C
        case 0x1A: rr(reg_de.hi); break; // RR D
        case 0x1B: rr(reg_de.lo); break; // RR E
        case 0x1C: rr(reg_hl.hi); break; // RR H
        case 0x1D: rr(reg_hl.lo); break; // RR L
        case 0x1E: rr_hl(); break; // RR (HL)

        case 0x27: sla(reg_af.hi); break; // SLA A
        case 0x20: sla(reg_bc.hi); break; // SLA B
        case 0x21: sla(reg_bc.lo); break; // SLA C
        case 0x22: sla(reg_de.hi); break; // SLA D
        case 0x23: sla(reg_de.lo); break; // SLA E
        case 0x24: sla(reg_hl.hi); break; // SLA H
        case 0x25: sla(reg_hl.lo); break; // SLA L
        case 0x26: sla_hl(); break; // SLA (HL)

        case 0x2F: sra(reg_af.hi); break; // SRA A
        case 0x28: sra(reg_bc.hi); break; // SRA B
        case 0x29: sra(reg_bc.lo); break; // SRA C
        case 0x2A: sra(reg_de.hi); break; // SRA D
        case 0x2B: sra(reg_de.lo); break; // SRA E
        case 0x2C: sra(reg_hl.hi); break; // SRA H
        case 0x2D: sra(reg_hl.lo); break; // SRA L
        case 0x2E: sra_hl(); break; // SRA (HL)

        case 0x3F: srl(reg_af.hi); break; // SRL A
        case 0x38: srl(reg_bc.hi); break; // SRL B
        case 0x39: srl(reg_bc.lo); break; // SRL C
        case 0x3A: srl(reg_de.hi); break; // SRL D
        case 0x3B: srl(reg_de.lo); break; // SRL E
        case 0x3C: srl(reg_hl.hi); break; // SRL H
        case 0x3D: srl(reg_hl.lo); break; // SRL L
        case 0x3E: srl_hl(); break; // SRL (HL)    

        //BIT b, reg
        case 0x40: bit(reg_bc.hi, 0); break; // BIT 0, B
        case 0x41: bit(reg_bc.lo, 0); break; // BIT 0, C
        case 0x42: bit(reg_de.hi, 0); break; // BIT 0, D
        case 0x43: bit(reg_de.lo, 0); break; // BIT 0, E
        case 0x44: bit(reg_hl.hi, 0); break; // BIT 0, H
        case 0x45: bit(reg_hl.lo, 0); break; // BIT 0, L
        case 0x46: bit_hl(0); break; // BIT 0, (HL)
        case 0x47: bit(reg_af.hi, 0); break; // BIT 0, A

        case 0x48: bit(reg_bc.hi, 1); break; // BIT 1, B
        case 0x49: bit(reg_bc.lo, 1); break; // BIT 1, C
        case 0x4A: bit(reg_de.hi, 1); break; // BIT 1, D
        case 0x4B: bit(reg_de.lo, 1); break; // BIT 1, E
        case 0x4C: bit(reg_hl.hi, 1); break; // BIT 1, H
        case 0x4D: bit(reg_hl.lo, 1); break; // BIT 1, L
        case 0x4E: bit_hl(1); break; // BIT 1, (HL)
        case 0x4F: bit(reg_af.hi, 1); break; // BIT 1, A

        case 0x50: bit(reg_bc.hi, 2); break; // BIT 2, B
        case 0x51: bit(reg_bc.lo, 2); break; // BIT 2, C
        case 0x52: bit(reg_de.hi, 2); break; // BIT 2, D
        case 0x53: bit(reg_de.lo, 2); break; // BIT 2, E
        case 0x54: bit(reg_hl.hi, 2); break; // BIT 2, H
        case 0x55: bit(reg_hl.lo, 2); break; // BIT 2, L
        case 0x56: bit_hl(2); break; // BIT 2, (HL)
        case 0x57: bit(reg_af.hi, 2); break; // BIT 2, A    

        case 0x58: bit(reg_bc.hi, 3); break; // BIT 3, B
        case 0x59: bit(reg_bc.lo, 3); break; // BIT 3, C
        case 0x5A: bit(reg_de.hi, 3); break; // BIT 3, D
        case 0x5B: bit(reg_de.lo, 3); break; // BIT 3, E
        case 0x5C: bit(reg_hl.hi, 3); break; // BIT 3, H
        case 0x5D: bit(reg_hl.lo, 3); break; // BIT 3, L
        case 0x5E: bit_hl(3); break; // BIT 3, (HL)
        case 0x5F: bit(reg_af.hi, 3); break; // BIT 3, A   

        case 0x60: bit(reg_bc.hi, 4); break; // BIT 4, B
        case 0x61: bit(reg_bc.lo, 4); break; // BIT 4, C
        case 0x62: bit(reg_de.hi, 4); break; // BIT 4, D
        case 0x63: bit(reg_de.lo, 4); break; // BIT 4, E
        case 0x64: bit(reg_hl.hi, 4); break; // BIT 4, H
        case 0x65: bit(reg_hl.lo, 4); break; // BIT 4, L
        case 0x66: bit_hl(4); break; // BIT 4, (HL)
        case 0x67: bit(reg_af.hi, 4); break; // BIT 4, A   

        case 0x68: bit(reg_bc.hi, 5); break; // BIT 5, B
        case 0x69: bit(reg_bc.lo, 5); break; // BIT 5, C
        case 0x6A: bit(reg_de.hi, 5); break; // BIT 5, D
        case 0x6B: bit(reg_de.lo, 5); break; // BIT 5, E
        case 0x6C: bit(reg_hl.hi, 5); break; // BIT 5, H
        case 0x6D: bit(reg_hl.lo, 5); break; // BIT 5, L
        case 0x6E: bit_hl(5); break; // BIT 5, (HL)
        case 0x6F: bit(reg_af.hi, 5); break; // BIT 5, A 

        case 0x70: bit(reg_bc.hi, 6); break; // BIT 6, B
        case 0x71: bit(reg_bc.lo, 6); break; // BIT 6, C
        case 0x72: bit(reg_de.hi, 6); break; // BIT 6, D
        case 0x73: bit(reg_de.lo, 6); break; // BIT 6, E
        case 0x74: bit(reg_hl.hi, 6); break; // BIT 6, H
        case 0x75: bit(reg_hl.lo, 6); break; // BIT 6, L
        case 0x76: bit_hl(6); break; // BIT 6, (HL)
        case 0x77: bit(reg_af.hi, 6); break; // BIT 6, A   

        case 0x78: bit(reg_bc.hi, 7); break; // BIT 7, B
        case 0x79: bit(reg_bc.lo, 7); break; // BIT 7, C
        case 0x7A: bit(reg_de.hi, 7); break; // BIT 7, D
        case 0x7B: bit(reg_de.lo, 7); break; // BIT 7, E
        case 0x7C: bit(reg_hl.hi, 7); break; // BIT 7, H
        case 0x7D: bit(reg_hl.lo, 7); break; // BIT 7, L
        case 0x7E: bit_hl(7); break; // BIT 7, (HL)
        case 0x7F: bit(reg_af.hi, 7); break; // BIT 7, A         

        // SET b, reg
        case 0xC0: set(reg_bc.hi, 0); break; // SET 0, B
        case 0xC1: set(reg_bc.lo, 0); break; // SET 0, C
        case 0xC2: set(reg_de.hi, 0); break; // SET 0, D
        case 0xC3: set(reg_de.lo, 0); break; // SET 0, E
        case 0xC4: set(reg_hl.hi, 0); break; // SET 0, H
        case 0xC5: set(reg_hl.lo, 0); break; // SET 0, L
        case 0xC6: set_hl(0); break; // SET 0, (HL)
        case 0xC7: set(reg_af.hi, 0); break; // SET 0, A

        case 0xC8: set(reg_bc.hi, 1); break; // SET 1, B
        case 0xC9: set(reg_bc.lo, 1); break; // SET 1, C
        case 0xCA: set(reg_de.hi, 1); break; // SET 1, D
        case 0xCB: set(reg_de.lo, 1); break; // SET 1, E
        case 0xCC: set(reg_hl.hi, 1); break; // SET 1, H
        case 0xCD: set(reg_hl.lo, 1); break; // SET 1, L
        case 0xCE: set_hl(1); break; // SET 1, (HL)
        case 0xCF: set(reg_af.hi, 1); break; // SET 1, A

        case 0xD0: set(reg_bc.hi, 2); break; // SET 2, B
        case 0xD1: set(reg_bc.lo, 2); break; // SET 2, C
        case 0xD2: set(reg_de.hi, 2); break; // SET 2, D
        case 0xD3: set(reg_de.lo, 2); break; // SET 2, E
        case 0xD4: set(reg_hl.hi, 2); break; // SET 2, H
        case 0xD5: set(reg_hl.lo, 2); break; // SET 2, L
        case 0xD6: set_hl(2); break; // SET 2, (HL)
        case 0xD7: set(reg_af.hi, 2); break; // SET 2, A

        case 0xD8: set(reg_bc.hi, 3); break; // SET 3, B
        case 0xD9: set(reg_bc.lo, 3); break; // SET 3, C
        case 0xDA: set(reg_de.hi, 3); break; // SET 3, D
        case 0xDB: set(reg_de.lo, 3); break; // SET 3, E
        case 0xDC: set(reg_hl.hi, 3); break; // SET 3, H
        case 0xDD: set(reg_hl.lo, 3); break; // SET 3, L
        case 0xDE: set_hl(3); break; // SET 3, (HL)
        case 0xDF: set(reg_af.hi, 3); break; // SET 3, A

        case 0xE0: set(reg_bc.hi, 4); break; // SET 4, B
        case 0xE1: set(reg_bc.lo, 4); break; // SET 4, C
        case 0xE3: set(reg_de.lo, 4); break; // SET 4, E
        case 0xE4: set(reg_hl.hi, 4); break; // SET 4, H
        case 0xE5: set(reg_hl.lo, 4); break; // SET 4, L
        case 0xE6: set_hl(4); break; // SET 4, (HL)
        case 0xE7: set(reg_af.hi, 4); break; // SET 4, A

        case 0xE8: set(reg_bc.hi, 5); break; // SET 5, B
        case 0xE9: set(reg_bc.lo, 5); break; // SET 5, C
        case 0xEA: set(reg_de.hi, 5); break; // SET 5, D
        case 0xEB: set(reg_de.lo, 5); break; // SET 5, E
        case 0xEC: set(reg_hl.hi, 5); break; // SET 5, H
        case 0xED: set(reg_hl.lo, 5); break; // SET 5, L
        case 0xEE: set_hl(5); break; // SET 5, (HL)
        case 0xEF: set(reg_af.hi, 5); break; // SET 5, A

        case 0xF0: set(reg_bc.hi, 6); break; // SET 6, B
        case 0xF1: set(reg_bc.lo, 6); break; // SET 6, C
        case 0xF2: set(reg_de.hi, 6); break; // SET 6, D
        case 0xF3: set(reg_de.lo, 6); break; // SET 6, E
        case 0xF4: set(reg_hl.hi, 6); break; // SET 6, H
        case 0xF5: set(reg_hl.lo, 6); break; // SET 6, L
        case 0xF6: set_hl(6); break; // SET 6, (HL)
        case 0xF7: set(reg_af.hi, 6); break; // SET 6, A

        case 0xF8: set(reg_bc.hi, 7); break; // SET 7, B
        case 0xF9: set(reg_bc.lo, 7); break; // SET 7, C
        case 0xFA: set(reg_de.hi, 7); break; // SET 7, D
        case 0xFB: set(reg_de.lo, 7); break; // SET 7, E
        case 0xFC: set(reg_hl.hi, 7); break; // SET 7, H
        case 0xFD: set(reg_hl.lo, 7); break; // SET 7, L
        case 0xFE: set_hl(7); break; // SET 7, (HL)
        case 0xFF: set(reg_af.hi, 7); break; // SET 7, A

        // RES n, reg
        case 0x80: res(reg_bc.hi, 0); break; // RES 0, B
        case 0x81: res(reg_bc.lo, 0); break; // RES 0, C
        case 0x82: res(reg_de.hi, 0); break; // RES 0, D
        case 0x83: res(reg_de.lo, 0); break; // RES 0, E
        case 0x84: res(reg_hl.hi, 0); break; // RES 0, H
        case 0x85: res(reg_hl.lo, 0); break; // RES 0, L
        case 0x86: res_hl(0); break; // RES 0, (HL)
        case 0x87: res(reg_af.hi, 0); break; // RES 0, A

        case 0x88: res(reg_bc.hi, 1); break; // RES 1, B
        case 0x89: res(reg_bc.lo, 1); break; // RES 1, C
        case 0x8A: res(reg_de.hi, 1); break; // RES 1, D
        case 0x8B: res(reg_de.lo, 1); break; // RES 1, E
        case 0x8C: res(reg_hl.hi, 1); break; // RES 1, H
        case 0x8D: res(reg_hl.lo, 1); break; // RES 1, L
        case 0x8E: res_hl(1); break; // RES 1, (HL)
        case 0x8F: res(reg_af.hi, 1); break; // RES 1, A

        case 0x90: res(reg_bc.hi, 2); break; // RES 2, B
        case 0x91: res(reg_bc.lo, 2); break; // RES 2, C
        case 0x92: res(reg_de.hi, 2); break; // RES 2, D
        case 0x93: res(reg_de.lo, 2); break; // RES 2, E
        case 0x94: res(reg_hl.hi, 2); break; // RES 2, H
        case 0x95: res(reg_hl.lo, 2); break; // RES 2, L
        case 0x96: res_hl(2); break; // RES 2, (HL)
        case 0x97: res(reg_af.hi, 2); break; // RES 2, A

        case 0x98: res(reg_bc.hi, 3); break; // RES 3, B
        case 0x99: res(reg_bc.lo, 3); break; // RES 3, C
        case 0x9A: res(reg_de.hi, 3); break; // RES 3, D
        case 0x9B: res(reg_de.lo, 3); break; // RES 3, E
        case 0x9C: res(reg_hl.hi, 3); break; // RES 3, H
        case 0x9D: res(reg_hl.lo, 3); break; // RES 3, L
        case 0x9E: res_hl(3); break; // RES 3, (HL)
        case 0x9F: res(reg_af.hi, 3); break; // RES 3, A

        case 0xA0: res(reg_bc.hi, 4); break; // RES 4, B
        case 0xA1: res(reg_bc.lo, 4); break; // RES 4, C
        case 0xA2: res(reg_de.hi, 4); break; // RES 4, D
        case 0xA3: res(reg_de.lo, 4); break; // RES 4, E
        case 0xA4: res(reg_hl.hi, 4); break; // RES 4, H
        case 0xA5: res(reg_hl.lo, 4); break; // RES 4, L
        case 0xA6: res_hl(4); break; // RES 4, (HL)
        case 0xA7: res(reg_af.hi, 4); break; // RES 4, A

        case 0xA8: res(reg_bc.hi, 5); break; // RES 5, B
        case 0xA9: res(reg_bc.lo, 5); break; // RES 5, C
        case 0xAA: res(reg_de.hi, 5); break; // RES 5, D
        case 0xAB: res(reg_de.lo, 5); break; // RES 5, E
        case 0xAC: res(reg_hl.hi, 5); break; // RES 5, H
        case 0xAD: res(reg_hl.lo, 5); break; // RES 5, L
        case 0xAE: res_hl(5); break; // RES 5, (HL)
        case 0xAF: res(reg_af.hi, 5); break; // RES 5, A

        case 0xB0: res(reg_bc.hi, 6); break; // RES 6, B
        case 0xB1: res(reg_bc.lo, 6); break; // RES 6, C
        case 0xB2: res(reg_de.hi, 6); break; // RES 6, D
        case 0xB3: res(reg_de.lo, 6); break; // RES 6, E
        case 0xB4: res(reg_hl.hi, 6); break; // RES 6, H
        case 0xB5: res(reg_hl.lo, 6); break; // RES 6, L
        case 0xB6: res_hl(6); break; // RES 6, (HL)
        case 0xB7: res(reg_af.hi, 6); break; // RES 6, A

        case 0xB8: res(reg_bc.hi, 7); break; // RES 7, B
        case 0xB9: res(reg_bc.lo, 7); break; // RES 7, C
        case 0xBA: res(reg_de.hi, 7); break; // RES 7, D
        case 0xBB: res(reg_de.lo, 7); break; // RES 7, E
        case 0xBC: res(reg_hl.hi, 7); break; // RES 7, H
        case 0xBD: res(reg_hl.lo, 7); break; // RES 7, L
        case 0xBE: res_hl(7); break; // RES 7, (HL)
        case 0xBF: res(reg_af.hi, 7); break; // RES 7, A

        default: 
        {
            fmt::print("CB OPCODE UNKNOWN\n");
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
//16 bit LD
//ld n, nn
void CPU::ld_n_nn(uint16_t &reg)
{
    cycles += 12;

    uint8_t hi = fetch_byte();
    uint8_t lo = fetch_byte();
    uint16_t nn = (hi << 8) | lo;
    
    reg = nn;
}
//ld SP, HL
void CPU::ld_sp_hl()
{
    increment_cycle();
    increment_cycle();

    reg_sp.reg = reg_hl.reg;
}
//ld HL,SP + n
void CPU::ld_hl_sp()
{
    cycles += 12;//TODO

    int8_t n = fetch_byte();
    reg_hl.reg = reg_sp.reg + n;

    flag_z = false;
    
    flag_n = false;

    flag_h = ( (reg_sp.reg & 0b1111) + ((uint8_t)n & 0b1111) > 0b1111);

    flag_c = ( (reg_sp.reg & 0b1111'1111) + ((uint8_t)n & 0b1111'1111) > 0b1111'1111);
}
//ld (nn), SP
void CPU::ld_nn_sp()
{
    cycles += 20;//TODO

    //CHECK
    uint8_t lo = fetch_byte();
    uint8_t hi = fetch_byte();
    uint16_t nn = (hi << 8) | lo;

    memory.write(nn, reg_sp.lo);
    nn++;
    memory.write(nn, reg_sp.hi);
}
//push nn
void CPU::sp_push(uint16_t &reg)
{
    cycles += 16;//TODO

    reg_sp.reg--;
    uint8_t hi = (reg >> 8);
    memory.write(reg_sp.reg, hi);
   
    reg_sp.reg--;
    uint8_t lo = (reg & 0b1111'1111);
    memory.write(reg_sp.reg, lo);
}
//pop nn
void CPU::sp_pop(uint16_t &reg)
{
    cycles += 12;//TODO

    uint8_t lo = memory.read(reg_sp.reg);
    reg_sp.reg++;

    uint8_t hi = memory.read(reg_sp.reg);
    reg_sp.reg++;

    reg = (hi << 8) | lo;
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
   
    flag_h = ((reg & 0b1111) == 0b1111); // if last 4 bits are 1s, then there was halfcarry
}

void CPU::dec_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    dec_reg(n);
    memory.write(reg_hl.reg, n);
}

//16 bit ALU
// ADD HL, reg
void CPU::add_hl(uint16_t &reg)
{
    increment_cycle();
    increment_cycle();

    reg_hl.reg = reg_hl.reg + reg;

    flag_n = false;

    flag_h = ( (reg_hl.reg & 0b1111'1111'1111) + (reg & 0b1111'1111'1111) > 0b1111'1111'1111);// set if overflow from bit 11

    flag_c = ( (reg_hl.reg & 0b1111'1111'1111'1111) + (reg & 0b1111'1111'1111'1111) > 0b1111'1111'1111'1111); // set if overflow from bit 15
}
// ADD SP, n
void CPU::add_sp()
{
    cycles += 16;//TODO

    int8_t n = fetch_byte();

    reg_sp.reg += n;

    flag_z = false;

    flag_n = false;

    flag_h = ( (reg_hl.reg & 0b1111) + ((uint8_t)n & 0b1111) > 0b1111);// set if overflow from bit 3

    flag_c = ( (reg_hl.reg & 0b1111'1111) + ((uint8_t)n & 0b1111'1111) > 0b1111'1111); // set if overflow from bit 7
}
// INC reg
void CPU::inc_nn(uint16_t &reg)
{
    increment_cycle();
    increment_cycle();

    reg++;
}
// DEC reg
void CPU::dec_nn(uint16_t &reg)
{
    increment_cycle();
    increment_cycle();

    reg--;
}

//misc
// CPL
void CPU::cpl()
{
    increment_cycle();
    reg_af.hi = ~reg_af.hi;
   
    flag_n = true;
   
    flag_h = true;
}
// CCF
void CPU::ccf()
{
    increment_cycle();

    flag_n = false;

    flag_h = false;

    flag_c = !flag_c;
}
// SCF
void CPU::scf()
{
    increment_cycle();

    flag_n = false;

    flag_h = false;

    flag_c = true;
}
// HALT
void CPU::halt()
{
    increment_cycle();

    halted = true;
}
// STOP
void CPU::stop()
{
    increment_cycle();

    halted = true;
}
// DI
void CPU::di()
{
    increment_cycle();

    interrupt_enabled = false;
}
// EI
void CPU::ei()
{
    increment_cycle();

    interrupt_enabled = true;
}
// DAA
// http://z80-heaven.wikidot.com/instructions-set:daa
// https://ehaskins.com/2018-01-30%20Z80%20DAA/
void CPU::daa()
{
    increment_cycle();

    uint8_t correction {};

    if(flag_h || (!flag_n && (reg_af.hi & 0b1111) > 0b1001 ) ) 
    {
        correction |= 0x06;
    }

    if(flag_c || (!flag_n && ((reg_af.hi >> 4) & 0b1111) > 0b1001 ) )
    {
        correction |= 0x60;
        flag_c = true;
    }

    reg_af.hi += flag_n ? -correction : correction;

    flag_z = (reg_af.hi == 0);

    flag_h = false;
}
// SWAP
void CPU::swap(uint8_t &reg)
{
    increment_cycle();
    increment_cycle();

    //get hi nibble
    uint8_t temp = (reg >> 4);
    //move lo nibble to hi and add temp
    reg = (reg << 4) | temp;

    flag_z = (reg == 0);

    flag_n = false;

    flag_h = false;

    flag_c = false;
}
// SWAP (HL)
void CPU::swap_hl()
{
    increment_cycle();
    increment_cycle();

    uint8_t n = memory.read(reg_hl.reg);
    swap(n);
    memory.write(reg_hl.reg, n);
}

//rotates and shifts
// RLCA
void CPU::rlca()
{
    increment_cycle();

    bool msb = reg_af.hi & (1 << 7);

    reg_af.hi = (reg_af.hi << 1) | ((uint8_t)msb);

    flag_z = false;

    flag_n = false;

    flag_h = false;

    flag_c = msb;
} 
// RLC
// http://z80-heaven.wikidot.com/instructions-set:rlc
void CPU::rlc(uint8_t &reg)
{
    increment_cycle();
    increment_cycle();

    bool msb = reg  & (1 << 7);

    reg = (reg << 1) | ((uint8_t)msb);

    flag_z = (reg == 0);

    flag_n = false;

    flag_h = false;

    flag_c = msb;
}
// RLC (HL)
void CPU::rlc_hl()
{
    increment_cycle();
    increment_cycle();

    uint8_t n = memory.read(reg_hl.reg);
    rlc(n);
    memory.write(reg_hl.reg, n);
}
// RLA
void CPU::rla()
{
    increment_cycle();

    bool msb = reg_af.hi & (1 << 7);
    bool carry = flag_c;
    reg_af.hi = (reg_af.hi << 1) | ((uint8_t)carry);

    flag_z = false;

    flag_n = false;

    flag_h = false;

    flag_c = msb;
}
// RL reg
void CPU::rl(uint8_t &reg)
{
    increment_cycle();
    increment_cycle();

    bool msb = reg & (1 << 7);
    bool carry = flag_c;
    reg = (reg << 1) | ((uint8_t) carry);

    flag_z = (reg == 0);

    flag_n = false;

    flag_h = false;

    flag_c = msb;
}
// RL (HL)
void CPU::rl_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    rl(n);
    memory.write(reg_hl.reg, n);
}
// RRA
void CPU::rra()
{
    increment_cycle();

    uint8_t carry = flag_c << 7;
    uint8_t lsb = reg_af.hi & 0x1;
    reg_af.hi = reg_af.hi | carry;
    reg_af.hi = (reg_af.hi >> 1);

    flag_z = false;

    flag_n = false;

    flag_h = false;

    flag_c = lsb;
}
// RRCA
void CPU::rrca()
{
    increment_cycle();

    bool lsb = reg_af.hi & 0x1;
    reg_af.hi = (reg_af.hi >> 1) | ((uint8_t)lsb << 7);

    flag_z = false;

    flag_n = false;

    flag_h = false;

    flag_c = lsb;
}
// RRC reg
void CPU::rrc(uint8_t &reg)
{
    increment_cycle();
    increment_cycle();

    bool lsb = reg & 0x1;
    reg = (reg >> 1) | ((uint8_t)lsb << 7);

    flag_z = (reg == 0);

    flag_n = false;

    flag_h = false;

    flag_c = lsb;
}
// RRC (HL)
void CPU::rrc_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    rrc(n);
    memory.write(reg_hl.reg, n);
}
// RR reg
void CPU::rr(uint8_t &reg)
{
    increment_cycle();
    increment_cycle();

    uint8_t carry = flag_c << 7;
    uint8_t lsb = reg & 0x1;
    reg = reg | carry;
    reg = (reg >> 1);

    flag_z = (reg == 0);

    flag_n = false;

    flag_h = false;

    flag_c = lsb;
}
// RR (HL)
void CPU::rr_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    rr(n);
    memory.write(reg_hl.reg, n);
}
// SLA reg
void CPU::sla(uint8_t &reg)
{
    increment_cycle();
    increment_cycle();

    bool msb = reg & (1 << 7);
    reg = reg << 1;

    flag_z = (reg == 0);

    flag_n = false;

    flag_h = false;

    flag_c = msb;
}
// SLA [HL]
void CPU::sla_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    sla(n);
    memory.write(reg_hl.reg, n);
}
// SRA reg
void CPU::sra(uint8_t &reg)
{
    increment_cycle();
    increment_cycle();

    bool lsb = reg & 0x1;
    bool msb = reg & (1 << 7);
    reg = (reg >> 1) | ((uint8_t)msb);

    flag_z = (reg == 0);

    flag_n = false;

    flag_h = false;

    flag_c = lsb;
}
// SRA [HL]
void CPU::sra_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    sra(n);
    memory.write(reg_hl.reg, n);
}
// SRL reg
// http://jgmalcolm.com/z80/advanced/shif#sla
void CPU::srl(uint8_t &reg)
{
    increment_cycle();
    increment_cycle();

    bool lsb = reg & 0x1;
    reg = reg >> 1;

    flag_z = (reg == 0);

    flag_n = false;

    flag_h = false;

    flag_c = lsb;
}
// SRL [HL]
void CPU::srl_hl()
{
    increment_cycle();
    increment_cycle();
    uint8_t n = memory.read(reg_hl.reg);
    srl(n);
    memory.write(reg_hl.reg, n);
}
// BIT n, reg
void CPU::bit(uint8_t &reg, uint8_t b)
{
    increment_cycle();
    increment_cycle();

    uint8_t result = reg & (1 << b);

    flag_z = (result == 0);

    flag_n = false;

    flag_h = true;
}
// BIT n, (HL)
void CPU::bit_hl(uint8_t b)
{
    increment_cycle();
    increment_cycle();

    uint8_t n = memory.read(reg_hl.reg);
    bit(n, b);
    memory.write(reg_hl.reg, n);
}
// SET n, reg
void CPU::set(uint8_t &reg, uint8_t b)
{
    increment_cycle();
    increment_cycle();

    reg = reg | (1 << b);
}
// SET n, (HL)
void CPU::set_hl(uint8_t b)
{
    increment_cycle();
    increment_cycle();

    uint8_t n = memory.read(reg_hl.reg);
    set(n, b);
    memory.write(reg_hl.reg, n);
}
// RES n, reg
void CPU::res(uint8_t &reg, uint8_t b)
{
    increment_cycle();
    increment_cycle();

    reg = reg & (~(1 << b));
}
// RES n, (HL)
void CPU::res_hl(uint8_t b)
{
    increment_cycle();
    increment_cycle();

    uint8_t n = memory.read(reg_hl.reg);
    res(n, b);
    memory.write(reg_hl.reg, n);
}
//JUMPs
//helper
void CPU::jump()
{
    uint8_t lo = fetch_byte();
    uint8_t hi = fetch_byte();
    uint16_t nn = (hi << 8) | lo;

    reg_pc.reg = nn;
}
// JP nn
void CPU::jp_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();
    increment_cycle();

    jump();
}
// JP NZ, nn
void CPU::jp_nz_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();
    increment_cycle();

    if(!flag_z)
        jump();
}
// JP Z, nn
void CPU::jp_z_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();
    increment_cycle();

    if(flag_z)
        jump();   
}
// JP NC, nn
void CPU::jp_nc_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();
    increment_cycle();

    if(!flag_c)
        jump();    
}
// JP C, nn
void CPU::jp_c_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();
    increment_cycle();

    if(flag_c)
        jump();    
}
// JP HL
void CPU::jp_hl()
{
    increment_cycle();

    reg_pc.reg = reg_hl.reg;
}
//helper
void CPU::jr_jump()
{
    increment_cycle();

    uint8_t n = fetch_byte();
    reg_pc.reg += n; 
}
// JR n
void CPU::jr()
{
    increment_cycle();
    increment_cycle();

    jr_jump();
}
// JR NZ
void CPU::jr_nz()
{
    increment_cycle();
    increment_cycle();

    if(!flag_z)
        jr_jump();
}
// JR Z
void CPU::jr_z()
{
    increment_cycle();
    increment_cycle();

    if(flag_z)
        jr_jump();
}
// JR NC
void CPU::jr_nc()
{
    increment_cycle();
    increment_cycle();

    if(!flag_c)
        jr_jump();
}
// JR C
void CPU::jr_c()
{
    increment_cycle();
    increment_cycle();

    if(flag_c)
        jr_jump();
}
//calls
//helper
void CPU::call()
{   
    increment_cycle();
    increment_cycle();
    increment_cycle();  

    reg_sp.reg--;
    memory.write(reg_sp.reg, reg_pc.hi);
    reg_sp.reg--;
    memory.write(reg_sp.reg, reg_pc.lo);  

    jump();
}
// CALL nn
void CPU::call_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();

    call();
}
// CALL NZ
void CPU::call_nz_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();

    if(!flag_z)
        call();
}
// CALL Z
void CPU::call_z_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();

    if(flag_z)
        call();
}
// CALL NC
void CPU::call_nc_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();

    if(!flag_c)
        call();
}
// CALL C
void CPU::call_c_nn()
{
    increment_cycle();
    increment_cycle();
    increment_cycle();

    if(flag_c)
        call();
}
//restart
// RST n
void CPU::rst_n(uint8_t n)
{
    //cycles += 32;
    increment_cycle();
    increment_cycle();
    increment_cycle();
    increment_cycle();

    increment_cycle();
    increment_cycle();
    increment_cycle();
    increment_cycle();
    
    reg_sp.reg--;
    memory.write(reg_sp.reg, reg_pc.hi);
    reg_sp.reg--;
    memory.write(reg_sp.reg, reg_pc.lo);

    reg_pc.reg = n;
}
//returns
//helper
void CPU::ret_from_subroutine()
{
    reg_sp.reg++;
    uint8_t lo = memory.read(reg_sp.reg);
    reg_sp.reg++;
    uint8_t hi = memory.read(reg_sp.reg);
    uint16_t addr = (hi << 8) | lo;

    reg_pc.reg = addr;
}
// RET
void CPU::ret()
{
    increment_cycle();
    increment_cycle();

    ret_from_subroutine();
}
// RET NZ
void CPU::ret_nz()
{
    increment_cycle();
    increment_cycle(); 

    if(!flag_z)
        ret_from_subroutine();
}
// RET Z
void CPU::ret_z()
{
    increment_cycle();
    increment_cycle(); 

    if(flag_z)
        ret_from_subroutine();
}
// RET NC
void CPU::ret_nc()
{
    increment_cycle();
    increment_cycle(); 

    if(!flag_c)
        ret_from_subroutine();
}
// RET C
void CPU::ret_c()
{
    increment_cycle();
    increment_cycle(); 

    if(flag_c)
        ret_from_subroutine();
}
// RETI
void CPU::reti()
{
    increment_cycle();
    increment_cycle();

    ret_from_subroutine();

    interrupt_enabled = true;
}