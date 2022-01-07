#include <iostream>
#include <fmt/core.h>

#include "cpu.h"


int main()
{
    fmt::print("Gameboy emulator\n");

    CPU cpu;
    
    cpu.reg_pc.reg = 0x100;
    cpu.reg_sp.reg = 0xFFFE;


    //temp
    char step {};
    uint8_t opcode {};

    cpu.rom = fopen("tests/cpu_instrs.gb","rb");
    if(cpu.rom == nullptr)
        return 1;

    fmt::print("ROM Loaded!\n");


    do {
       step = getchar();

       fseek(cpu.rom, cpu.reg_pc.reg, SEEK_SET);
       fread(&opcode, sizeof(uint8_t), 1, cpu.rom);
       
       fmt::print("PC: {0:#x}\n", cpu.reg_pc.reg);
       fmt::print("opcode: {0:#x}\n", opcode);
        
       cpu.execute(opcode); 

    }while(step != 'e');

    fclose(cpu.rom);
    cpu.rom = nullptr;

    return 0;
}