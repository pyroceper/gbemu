#include <iostream>
#include <fmt/core.h>

#include "memory.h"
#include "cpu.h"


int main()
{
    fmt::print("Gameboy emulator\n");

    CPU cpu("tests/individual/06-ld r,r.gb");
    
    //temp
    cpu.reg_pc.reg = 0x100;
    cpu.reg_sp.reg = 0xFFFE;


    //temp
    char step {};
    uint8_t opcode {};

    do {
       step = getchar();

       opcode = cpu.memory.rom[cpu.reg_pc.reg];
       
       fmt::print("PC: {0:#x}\n", cpu.reg_pc.reg);
       fmt::print("opcode: {0:#x}\n", opcode);
        
       cpu.execute(opcode); 

    }while(step != 'e');

    return 0;
}