// https://github.com/kripod/chip8-roms
// https://www.freecodecamp.org/news/creating-your-very-own-chip-8-emulator/
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1

#include <assert.h>
#include <memory.h>
#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define SCREEN_WIDTH    64
#define SCREEN_HEIGHT   32

char mem[4096];
char reg[16];

void outputMemory(char *a_Memory)
{

}

//void loadSprites(char **a_Memory)
//{
//    const int sprites[] = {
//        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
//        0x20, 0x60, 0x20, 0x20, 0x70, // 1
//        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
//        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
//        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
//        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
//        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
//        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
//        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
//        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
//        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
//        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
//        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
//        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
//        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
//        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
//    };
//
//    const int length = sizeof(sprites) / sizeof(sprites[0]);
//    for (int i = 0; i < length; i++)
//    {
//        *a_Memory[i] = sprites[i];
//    }
//}

void loadRoms(const char *a_Filename, char *a_Memory, short int a_Offset)
{
    FILE *rom = fopen(a_Filename, "rb");
    assert(NULL != rom && "Failed to open rom file.");

    fseek(rom, 0, SEEK_END);
    const long size = ftell(rom);
    fseek(rom, 0, SEEK_SET);

    char *ptr = a_Memory + a_Offset;
    fread(ptr, size, 1, rom);
    fclose(rom);
}

unsigned short fetchOpcode(const char *a_Mem, short int *a_PC)
{
    unsigned short opcode = a_Mem[*a_PC] << 8 | a_Mem[*a_PC + 1];
    *a_PC += 2;
    return opcode;
}

void updateTimers()
{

}

void playSound()
{

}

void render()
{

}

void execute(unsigned short int a_Opcode)
{
    const int x = (a_Opcode & 0x0F00) >> 8;
    const int y = (a_Opcode & 0x00F0) >> 4;
}

int main()
{
    // initialize
    memset(mem, 0, 4096);
    memset(reg, 0, 16);
    short int PC = 0x200;
    short int opcode = 0;
    short int I = 0;

    loadSprites(*mem);

    // read data
    loadRoms("roms/sirpinski.ch8", mem, PC);

    unsigned char paused = FALSE;
    unsigned int instructionsPerCycle = 10;
    char c = '\0';
    unsigned char running = TRUE;
    do
    {
        for (unsigned int i = 0; i < instructionsPerCycle; i++)
        {
            if (!paused)
            {
                opcode = fetchOpcode(mem, &PC);
                execute(opcode);
            }
        }

        if (!paused)
        {
            updateTimers();
        }

        playSound();
        render();

        c = getchar();
        running = (c != 'q');
    } while (running);

    return 0;
}
