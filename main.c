#include <stdio.h>
#include <stdint.h>
#include <signal.h>
/* unix only*/
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>
#include <Windows.h>
#include <conio.h>

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX]; // 65536 memory locations

/* Define LC-3 registers*/
enum
{
    R_RO = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /* Program counter*/
    R_COND,
    R_COUNT
};

/* Store registers in an array*/
uint16_t reg[R_COUNT];

/* Get LC-3 Opcodes*/
enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register*/
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused)*/
    OP_LEA,    /* load effective address */
    OP_TRAP,   /* execute trap */
};

// Define LC-3 condition flags
enum
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z*/
    FL_NEG = 1 << 2, /* N */
}

// Main loop
int
main(int argc, const char *argv[])
{
    /* Take command line argumnets*/
    if (argc < 2)
    {
        /* Show usage string*/
        printf("lc3 [image-file]...\n");
        exit(2)
    }

    for (int j = 1; j < argc; ++j)
    {
        if (!(read_image(argv[j])))
        {
            printf("Failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }
    /* Only one condition flag should be set*/
    /* Set Z flag*/
    reg[R_COND] = FL_ZRO;

    /* Set program counter to starting position*/
    /* 0x3000 is the default starting position*/
    enum
    {
        PC_START = 0X3000
    };
    reg[R_PC] = PC_START;

    int running = 1;
    while (running)
    {
        /* FETCH the next instruction from memory */
        uint16_t instruction = mem_read(reg[R_PC]++);
        uint16_t opcode = instruction >> 12;

        /* Execute an opcode*/
        switch (opcode)
        {
            case OP_ADD:
            {
                /* Get destination register from instruction*/
                uint16_t r0 = (instruction >> 9) & 0x7;
                /* Get first operand */
                uint16_t r1 = (instruction >> 6) & 0x7;
                /* Check whether we are in immediate mode */
                uint16_t imm_flag = (instruction >> 5) & 1;

                if (imm_flag)
                {
                    uint16_t imm5 = signExtend(instruction & 0X1F, 5);
                    reg[r0] = reg[r1] + imm5;
                }
                else
                {
                    uint16_t r2 = instruction & 0x7;
                    reg[r0] = reg[r1] + reg[r2];
                }

                updateFlags(r0);
            }
            break;
            case OP_AND:
                and() break;
            case OP_BR:
                br();
                break;
            case OP_JMP:
                jmp();
                break;
            case OP_JSR:
                jsr() break;
            case OP_LD:
                ld() break;
            case OP_LDI:
                ldi() break;
            case OP_LDR:
                ldr() break;
            case OP_LEA:
                lea() break;
            case OP_NOT:
                not() break;
            case OP_ST:
                st() break;
            case OP_STR():
                str() break;
            case OP_STI:
                sti() break;
            case OP_TRAP:
                trap() break;
            case OP_RES:
            case OP_RTI:
            default:
                bad_opcode() break;
            }
        }
    shutdown()
}

// Sign extend function
uint16_t signExtend(uint16_t bit_string, int bit_count)
{
    if ((bit_string >> (bit_count - 1)) & 1)
        bit_string |= (0XFFFF << bit_count);
    return bit_string
}

/* Any time a value is written in a register */
/* Update the flags to indicate its sign */
void updateFlags(uint16_t r)
{
    if (reg[r] == 0)
        reg[R_COND] = FL_ZRO;
    else if (reg[r] >> 15) /* A one in the left-most bit indicates a negative number*/
        reg[R_COND] = FL_NEG;
    else
        reg[R_COND] = FL_POS;
}