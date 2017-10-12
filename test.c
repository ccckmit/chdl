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

void testGate3() {
    printf("=========== testGate3() =============\n");
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

#define char2bit(c) ((c=='0')?0:1)
#define bit2char(b) ((b==0)?'0':'1')

void str2bits(char *str, BIT *bits) {
    int len = strlen(str);
    for (int i=0; i<len; i++) {
        bits[i] = char2bit(str[i]);
    }
}

void bits2str(BIT *bits, char *str, int len) {
    for (int i=0; i<len; i++) {
        str[i] = bit2char(bits[i]);
    }
    str[len] = '\0';
}

void lpad(char *str, char *padStr, int len) {
    char format[100];
    sprintf(format, "%%0%ds", len);
    sprintf(padStr, format, str);
}

void int2bits(int number, BIT *bits, int len) {
    char str[100], padStr[100];
    itoa(number, str, 2);
    lpad(str, padStr, len);
    strrev(padStr);
    str2bits(padStr, bits);
}

int bits2int(BIT *bits, int len) {
    char str[100];
    bits2str(bits, str, len);
    strrev(str);
    return strtol(str, (char **)NULL, 2);
}

#define ADDS 2

void testAdd16() {
    printf("=========== testAlu() =============\n");

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

void testChapter1() {
    testGate1();
    testGate2();
    testGate3();
}

void testChapter2() {
    testAdd16();
}

void test() {
    testChapter1();
    testChapter2();    
}

int main() {
    init();
    test();
}
