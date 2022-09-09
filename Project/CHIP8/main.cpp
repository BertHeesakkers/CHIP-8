// https://github.com/kripod/chip8-roms
// https://www.freecodecamp.org/news/creating-your-very-own-chip-8-emulator/
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1

#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

uint8_t mem[4096];
uint8_t reg[16];

void LoadRoms(const std::string &a_Filename, uint8_t *a_Memory, uint16_t a_Offset)
{
    std::ifstream rom(a_Filename, std::ios::binary);
    assert(rom.is_open());

    rom.seekg(0, std::ios::end);
    const std::streamsize size = rom.tellg();
    rom.seekg(0, std::ios::beg);

    uint8_t *ptr = (a_Memory + a_Offset);
    rom.read(reinterpret_cast<char *>(ptr), size);
}

uint16_t FetchOpcode(const uint16_t &a_Mem, uint16_t &a_PC)
{
    uint16_t opcode = mem[a_PC] << 8 | mem[a_PC + 1];
    a_PC += 2;
    return opcode;
}

void UpdateTimers()
{

}

void PlaySound()
{

}

void Render()
{

}

void Execute(uint16_t a_Opcode)
{
    const int x = (a_Opcode & 0x0F00) >> 8;
    const int y = (a_Opcode & 0x00F0) >> 4;
}

int main()
{
    // initialize
    memset(mem, 0, 4096);
    memset(reg, 0, 16);
    uint16_t PC = 0x200;
    uint16_t opcode = 0;
    uint16_t I = 0;

    // read data
    LoadRoms("sirpinski.ch8", mem, PC);

    bool paused = false;
    size_t instructionsPerCycle = 10;
    char c = '\0';
    bool running = true;
    do 
    {
        for (size_t i = 0; i < instructionsPerCycle; i++)
        {
            if (!paused)
            {
                opcode = FetchOpcode(*mem, PC);
                Execute(opcode);
            }
        }

        if (!paused)
        {
            UpdateTimers();
        }

        PlaySound();
        Render();

        c = std::cin.get();
        running = (c != 'q');
    } while (running);

    return 0;
}