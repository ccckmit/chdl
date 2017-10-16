#include "chdl.h"

void testGate1() {
    printf("=========== test1Gate() =============\n");
    BIT table[2] = {0,1};

    for (int i=0; i<2; i++) {
        BIT in = table[i];
        BIT o;

        printf("in=%d\n", in);

        not(in, &o);
        ASSERT(o == !in);
    }
}

void testGate2() {
    printf("=========== testGate2() =============\n");
    BIT table[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    
    for (int i=0; i<4; i++) {
        BIT a = table[i][0];
        BIT b = table[i][1];
        BIT o;

        printf("a=%d b=%d\n", a, b);

        nand(a, b, &o);
        ASSERT(o == !(a&&b));
    
        and(a, b, &o);
        ASSERT(o == (a&&b));
    
        or(a, b, &o);
        ASSERT(o == (a||b));
    
        xor(a, b, &o);
        ASSERT(o == (a^b));
    }        
}

void testFullAdder() {
    printf("=========== testFullAdder() =============\n");
    BIT table[8][3] = {{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
                       {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
    
    for (int i=0; i<8; i++) {
        BIT a = table[i][0];
        BIT b = table[i][1];
        BIT c = table[i][2];
        BIT sum, carry;

        fullAdder(a, b, c, &sum, &carry);
        printf("a=%d b=%d c=%d sum=%d carry=%d\n", a, b, c, sum, carry);
        ASSERT(sum == (a+b+c)%2);
        ASSERT(carry == (a+b+c)/2);
    }
}

void testMux() {
    printf("=========== testMux() =============\n");
    BIT table[8][3] = {{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
                       {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
    
    for (int i=0; i<8; i++) {
        BIT a = table[i][0];
        BIT b = table[i][1];
        BIT s = table[i][2];
        BIT o;

        mux(a, b, s, &o);
        printf("a=%d b=%d s=%d o=%d\n", a, b, s, o);
    }
}

void testDmux() {
    printf("=========== testDmux() =============\n");
    BIT table[4][4] = {{0,0,0,0}, {0,1,0,0}, {1,0,1,0}, {1,1,0,1}};
    for (int i=0; i<4; i++) {
        BIT in = table[i][0];
        BIT s  = table[i][1];
        BIT oa  = table[i][2];
        BIT ob  = table[i][3];
        BIT a,b;
        
        dmux(in, s, &a, &b);
        printf("in=%d s=%d a=%d b=%d\n", in, s, a, b);
        ASSERT(oa==a && ob==b);
    }    
}

void testDmux8way() {
    printf("=========== testDmux8way() =============\n");
    BIT e[8];
    for (int addr = 0; addr < 8; addr++) {
        BIT address[3];
        char estr[9];
        int2bits(addr, address, 3);
        dmux8way(1, address, &e[0], &e[1], &e[2], &e[3], &e[4], &e[5], &e[6], &e[7]);
        bits2str(e, estr, 8);
        printf("dmux8way:addr=%d e=%s\n", addr, estr);
        assert(e[addr] == 1);
    }   
}
    

#define ADDS 2

void testAdd16() {
    printf("=========== testAdd16() =============\n");

    int table[ADDS][3] = {{3,11,14}, {3000,2000,5000}};

    for (int i=0; i<ADDS; i++) {
        BIT a[16], b[16], c[16];
        int2bits(table[i][0], a, 16);
        int2bits(table[i][1], b, 16);
        add16(a, b, c);
        ASSERT(bits2int(c, 16) == table[i][2]);
        printf("a+b = %d\n", bits2int(c, 16));
    }
}

void testAlu() {
    printf("=========== testAlu() =============\n");

    int ia = 35, ib = 20;
    BIT a[W], b[W];
    int2bits(ia, a, W);
    int2bits(ib, b, W);
    printf("alu(35, 20) : 35=100011 20=010100\n");
    for (int i=0; i<AOPS; i++) {
        BIT out[W];
        BIT zr, ng;
        AOP p = aop[i];
        alu(a, b, p.zx, p.nx, p.zy, p.ny, p.f, p.no, out, &zr, &ng);
        WORD iout = bits2int(out, W);
        printf("alu:out= %04hx % 4d zr=%d ng=%d op=%s\n", iout, iout, zr, ng, p.op);
    }
}

void testBit() {
    printf("=========== testBit() =============\n");
    BIT in[]={1,1,1,0,1,1,0}, load[]={0,1,1,1,1,0,0}, out;
    WORD r;
    int i = 0;
    for (timer = 5; timer < 40; timer+=5, i++) {
        bit(&r, 0, in[i], load[i], &out);
        printf("%02d:r=%d in=%d load=%d out=%d\n", timer, r, in[i], load[i], out);
    }
}

void testRegister() {
    printf("=========== testRegister() =============\n");
    WORD in[] = {1,2,3,4,5,6,7,8}, load[]={0,1,1,1,1,0,0};
    WORD r = 374; // 0xFB07;
    int i = 0;
    for (timer = 5; timer < 40; timer+=5, i++) {
        BIT rin[W], rout[W];
        char rinStr[W+1];
        int2bits(in[i], rin, W);
        reg(&r, rin, load[i], rout);
        WORD routInt = bits2int(rout, W);
        WORD rinInt  = bits2int(rin, W);
        printf("%02d:r=%d rin=%d load=%d rout=%d\n", timer, r, rinInt, load[i], routInt);
    }
}

void dumpRam(WORD r[], int size) {
    printf("============ dumpRam =============\n");
    for (int i=0; i<size; i++) {
        printf("ram[%d] = %04x %d\n", i, r[i], r[i]);
    }
}

void testRam8() {
    printf("=========== testRam8() =============\n");
    WORD in[]   = {0,1,2,3,4,5,6,7,8,9};
    WORD addr[] = {3,2,1,0,7,3,2,1,0,5,6}; // {0,1,2,3,4,5,6,7,0,1,2}; // {1,4,7,1,4,7,1,4,7,1};
    WORD r[8]   = {90,91,92,93,94,95,96,97};
    BIT load[]  = {0,1,1,1,1,0,0,1,1,0}; // {0,0,0,0,0,0,0,0,0,0}; 
    int i = 0;
    dumpRam(r, 8);
    for (timer = 5; timer <= 50; timer+=5, i++) {
        BIT rin[W], rout[W], raddr[3];
        char rinStr[W+1], raddrStr[4];
        int2bits(in[i], rin, W);
        int2bits(addr[i], raddr, 3);
//        bits2str(raddr, raddrStr, 3);
//        printf("  raddrStr=%s\n", raddrStr);
        ram8(r, rin, load[i], raddr, rout);
        WORD routInt = bits2int(rout, W);
        WORD rinInt  = bits2int(rin, W);
        printf("%02d:rin=%2d load=%d addr=%d rout=%d\n", timer, rinInt, load[i], addr[i], routInt);
        dumpRam(r, 8);
    }
}

void testChapter1() {
    testGate1();
    testGate2();
    testFullAdder();
    testMux();
    testDmux();
    testDmux8way();
}

void testChapter2() {
    testAdd16();
    testAlu();
}

void testChapter3() {
    testBit();
    testRegister();
    testRam8();
}

void test() {
    testChapter1();
    testChapter2();
    testChapter3();
}

int main() {
    init();
    test();
}
