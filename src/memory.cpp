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

        fread(rom, sizeof(uint8_t), rom_size, rom_file);


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
    return rom[address];
}

void Memory::write(uint16_t address, uint8_t value)
{
    rom[address] = value;
}