#include "memory.h"

Memory::Memory(const std::string &path)
{
    load_ROM(path);
}


void Memory::load_ROM(const std::string &path)
{
    FILE *rom = fopen(path.c_str(), "rb");

    if(rom != nullptr)
    {
        fseek(rom, 0, SEEK_END);
        int rom_size = ftell(rom);
        fseek(rom, 0, SEEK_SET);

        fmt::print("ROM size: {}\n", rom_size);


        uint8_t opcode {};
        for(int i = 0;i < rom_size;i++)
        {
            fread(&opcode, sizeof(uint8_t), 1, rom);
            cartridge.push_back(opcode);
        }


        fmt::print("ROM Loaded!\n");
        fclose(rom);
    }
    else 
    {
        rom_load_fail = true;
        fmt::print("Failed to load ROM!\n");
    }

}