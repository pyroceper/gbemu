#include "memory.h"

void Memory::load_ROM(const std::string &path)
{
    FILE *rom_file = fopen(path.c_str(), "rb");

    if(rom_file != nullptr)
    {
        fseek(rom_file, 0, SEEK_END);
        int rom_size = ftell(rom_file);
        fseek(rom_file, 0, SEEK_SET);

        fmt::print("ROM size: {}\n", rom_size);

        uint8_t opcode {};
        for(int i = 0;i < rom_size;i++)
        {
            fread(&opcode, sizeof(uint8_t), 1, rom_file);
            cartridge.push_back(opcode);
        }


        fmt::print("ROM Loaded!\n");
        fclose(rom_file);
    }
    else 
    {
        fmt::print("Failed to load ROM!\n");
        exit(1);
    }

}

uint8_t Memory::read(uint16_t address)
{
    return cartridge[address];
}

void Memory::write(uint16_t address, uint8_t value)
{
    cartridge[address] = value;
}