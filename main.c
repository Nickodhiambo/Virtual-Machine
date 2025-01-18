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
uint16_t memory[MEMORY_MAX]; //65536 memory locations

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
    R_PC,  /* Program counter*/
    R_COND,
    R_COUNT
};

/* Store registers in an array*/
uint16_t reg[R_COUNT];


/* Get LC-3 Opcodes*/
enum
{
    OP_BR = 0, /* branch */
    OP_ADD, /* add */
    OP_LD, /* load */
    OP_ST, /* store */
    OP_JSR, /* jump register */
    OP_AND, /* bitwise and */
    OP_LDR, /* load register */
    OP_STR, /* store register*/
    OP_RTI, /* unused */
    OP_NOT, /* bitwise not */
    OP_LDI, /* load indirect */
    OP_STI, /* store indirect */
    OP_JMP, /* jump */
    OP_RES, /* reserved (unused)*/
    OP_LEA, /* load effective address */
    OP_TRAP, /* execute trap */
};

// Define LC-3 condition flags
enum{
    FL_POS = 1 << 0,  /* P */
    FL_ZRO = 1 << 2,  /* Z*/
    FL_POS = 1 << 2,  /* N */
}