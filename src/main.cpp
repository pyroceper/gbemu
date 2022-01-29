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
        
       cpu.execute(); 

    }while(step != 'e');

    return 0;
}