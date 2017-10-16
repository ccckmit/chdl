#define char2bit(c) ((c=='0')?0:1)
#define bit2char(b) ((b==0)?'0':'1')
#define setBit(r, i, bit) ( (r) ^= (-(bit) ^ (r)) & (1 << (i)))
#define getBit(r, i) (((r) >> (i)) & 1)

void str2bits(char *str, BIT *bits) {
    int len = strlen(str);
    for (int i=0; i<len; i++) {
        bits[len-i-1] = char2bit(str[i]);
    }
}

void bits2str(BIT *bits, char *str, int len) {
    for (int i=0; i<len; i++) {
        str[len-i-1] = bit2char(bits[i]);
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
//    strrev(padStr);    
    str2bits(padStr, bits);
}

int bits2int(BIT *bits, int len) {
    char str[100];
    bits2str(bits, str, len);
//    strrev(str);
    return strtol(str, (char **)NULL, 2);
}

void printBits(char *msg, BIT *bits, int len) {
    char str[len+1];
    bits2str(bits, str, len);
    printf("%s:%s\n", msg, str);
}
