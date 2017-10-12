void nand(BIT a, BIT b, BIT *o) {
    *o = !(a && b);
}

int timer = 0;

bool posEdge() {
    return (timer%10 == 0);
}

void dff(BIT *reg, BIT in, BIT *out) {
    if (posEdge()) *reg = in;
    *out = *reg;
}

#define W 16
#define K 1024
#define KW (K*W)
#define REGS_MAX (64*KW)

BIT regTable[REGS_MAX];
BIT *A, *D, *PC, *MEMORY, *RAM16K, *SCREEN, *KEYBOARD, *ROM32K;

void init() {
    A = &regTable[0];
    D = &A[W];
    PC= &D[W];
    
    MEMORY = &PC[W];
    RAM16K = MEMORY;
    SCREEN = &MEMORY[16*KW];
    KEYBOARD = &SCREEN[8*KW];
    
    ROM32K = &KEYBOARD[W];
}

#include "chapter1.c"
#include "chapter2.c"
#include "chapter3.c"
#include "chapter5.c"
