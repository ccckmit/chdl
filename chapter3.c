// ============= Chapter 3 ==================
int timer = 0;

bool posEdge() {
    return (timer%10 == 0);
}

void dff(WORD *r, int i, BIT in, BIT *out) {
//    *out = getBit(*r, i);
//    if (posEdge()) setBit(*r, i, in);
    *out = getBit(*r, i);
    if (posEdge()) setBit(*r, i, in);
}

void bit(WORD *r, int i, BIT in, BIT load, BIT *out) {
    BIT din, ri = getBit(*r,i);
//    mux(*out, in, load, &din);
    mux(ri, in, load, &din);
    dff(r, i, din, out);
}

void reg(WORD *r, BIT in[16], BIT load, BIT out[16]) {
    bit(r, 0,  in[0],  load, &out[0]);
    bit(r, 1,  in[1],  load, &out[1]);
    bit(r, 2,  in[2],  load, &out[2]);
    bit(r, 3,  in[3],  load, &out[3]);
    bit(r, 4,  in[4],  load, &out[4]);
    bit(r, 5,  in[5],  load, &out[5]);
    bit(r, 6,  in[6],  load, &out[6]);
    bit(r, 7,  in[7],  load, &out[7]);
    bit(r, 8,  in[8],  load, &out[8]);
    bit(r, 9,  in[9],  load, &out[9]);
    bit(r, 10, in[10], load, &out[10]);
    bit(r, 11, in[11], load, &out[11]);
    bit(r, 12, in[12], load, &out[12]);
    bit(r, 13, in[13], load, &out[13]);
    bit(r, 14, in[14], load, &out[14]);
    bit(r, 15, in[15], load, &out[15]);
}

void ram8(WORD r[8], BIT in[16], BIT load, BIT address[3], BIT out[16]) {
    BIT e[8],ld[8];
    BIT o[8][16];
    dmux8way(1, address, &e[0], &e[1], &e[2], &e[3], &e[4], &e[5], &e[6], &e[7]);
    and(load, e[0], &ld[0]); reg(&r[0], in, ld[0], o[0]);
    and(load, e[1], &ld[1]); reg(&r[1], in, ld[1], o[1]);
    and(load, e[2], &ld[2]); reg(&r[2], in, ld[2], o[2]);
    and(load, e[3], &ld[3]); reg(&r[3], in, ld[3], o[3]);
    and(load, e[4], &ld[4]); reg(&r[4], in, ld[4], o[4]);
    and(load, e[5], &ld[5]); reg(&r[5], in, ld[5], o[5]);
    and(load, e[6], &ld[6]); reg(&r[6], in, ld[6], o[6]);
    and(load, e[7], &ld[7]); reg(&r[7], in, ld[7], o[7]);
    mux8way16(o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7], address, out);
}

void ram64(WORD r[64], BIT in[16], BIT load, BIT address[6], BIT out[16]) {
    BIT e[8], ld[8];
    BIT o[8][W];
    dmux8way(1, &address[3], &e[0], &e[1], &e[2], &e[3], &e[4], &e[5], &e[6], &e[7]);
    and(load, e[0], &ld[0]); ram8(&r[0], in, ld[0], address, o[0]);
    and(load, e[1], &ld[1]); ram8(&r[1], in, ld[1], address, o[1]);
    and(load, e[2], &ld[2]); ram8(&r[2], in, ld[2], address, o[2]);
    and(load, e[3], &ld[3]); ram8(&r[3], in, ld[3], address, o[3]);
    and(load, e[4], &ld[4]); ram8(&r[4], in, ld[4], address, o[4]);
    and(load, e[5], &ld[5]); ram8(&r[5], in, ld[5], address, o[5]);
    and(load, e[6], &ld[6]); ram8(&r[6], in, ld[6], address, o[6]);
    and(load, e[7], &ld[7]); ram8(&r[7], in, ld[7], address, o[7]);
    mux8way16(o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7], &address[3], out);
}

void ram512(WORD r[512], BIT in[16], BIT load, BIT address[9], BIT out[16]) {
    BIT e[8], ld[8];
    BIT o[8][W];
    dmux8way(1, &address[6], &e[0], &e[1], &e[2], &e[3], &e[4], &e[5], &e[6], &e[7]);
    and(load, e[0], &ld[0]); ram8(&r[0], in, ld[0], address, o[0]);
    and(load, e[1], &ld[1]); ram8(&r[1], in, ld[1], address, o[1]);
    and(load, e[2], &ld[2]); ram8(&r[2], in, ld[2], address, o[2]);
    and(load, e[3], &ld[3]); ram8(&r[3], in, ld[3], address, o[3]);
    and(load, e[4], &ld[4]); ram8(&r[4], in, ld[4], address, o[4]);
    and(load, e[5], &ld[5]); ram8(&r[5], in, ld[5], address, o[5]);
    and(load, e[6], &ld[6]); ram8(&r[6], in, ld[6], address, o[6]);
    and(load, e[7], &ld[7]); ram8(&r[7], in, ld[7], address, o[7]);
    mux8way16(o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7], &address[6], out);
}

void ram4K(WORD r[4*K], BIT in[16], BIT load, BIT address[9], BIT out[16]) {
    BIT e[8], ld[8];
    BIT o[8][W];
    dmux8way(1, &address[9], &e[0], &e[1], &e[2], &e[3], &e[4], &e[5], &e[6], &e[7]);
    and(load, e[0], &ld[0]); ram8(&r[0], in, ld[0], address, o[0]);
    and(load, e[1], &ld[1]); ram8(&r[1], in, ld[1], address, o[1]);
    and(load, e[2], &ld[2]); ram8(&r[2], in, ld[2], address, o[2]);
    and(load, e[3], &ld[3]); ram8(&r[3], in, ld[3], address, o[3]);
    and(load, e[4], &ld[4]); ram8(&r[4], in, ld[4], address, o[4]);
    and(load, e[5], &ld[5]); ram8(&r[5], in, ld[5], address, o[5]);
    and(load, e[6], &ld[6]); ram8(&r[6], in, ld[6], address, o[6]);
    and(load, e[7], &ld[7]); ram8(&r[7], in, ld[7], address, o[7]);
    mux8way16(o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7], &address[9], out);
}

void ram16K(WORD r[16*K], BIT in[16], BIT load, BIT address[9], BIT out[16]) {
    BIT e[4], ld[4];
    BIT o[4][W];
    dmux4way(1, &address[12], &e[0], &e[1], &e[2], &e[3]);
    and(load, e[0], &ld[0]); ram8(&r[0], in, ld[0], address, o[0]);
    and(load, e[1], &ld[1]); ram8(&r[1], in, ld[1], address, o[1]);
    and(load, e[2], &ld[2]); ram8(&r[2], in, ld[2], address, o[2]);
    and(load, e[3], &ld[3]); ram8(&r[3], in, ld[3], address, o[3]);
    and(load, e[4], &ld[4]); ram8(&r[4], in, ld[4], address, o[4]);
    and(load, e[5], &ld[5]); ram8(&r[5], in, ld[5], address, o[5]);
    and(load, e[6], &ld[6]); ram8(&r[6], in, ld[6], address, o[6]);
    and(load, e[7], &ld[7]); ram8(&r[7], in, ld[7], address, o[7]);
    mux4way16(o[0], o[1], o[2], o[3], &address[12], out);
}

void pc(WORD r[1], BIT in[16], BIT load, BIT inc, BIT reset, BIT out[16]) {
    BIT loadInc, loadIncReset, if1[16], if2[16], if3[16], o[16], oInc[16];

    or(load, inc, &loadInc);
    or(loadInc, reset, &loadIncReset);
    reg(r, if3, loadIncReset, o);
    mux16(o,   oInc,  inc,   if1);
    mux16(if1,   in,  load,  if2);
    mux16(if2,    0,  reset, if3);
    inc16(o, oInc);
    and16(o, o, out);
}

/*
    Or(a=load, b=inc, out=loadInc);
    Or(a=loadInc, b=reset, out=loadIncReset);

    Register(in=if3, load=loadIncReset, out=o);
    Inc16(in=o, out=oInc);
    And16(a=o, b=o, out=out);
    
    Mux16(a=o,   b=oInc,  sel=inc,   out=if1);
    Mux16(a=if1, b=in,    sel=load,  out=if2);
    Mux16(a=if2, b=false,  sel=reset, out=if3);
}

*/
