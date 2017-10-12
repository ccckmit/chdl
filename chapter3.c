// ============= Chapter 3 ==================
void bit(BIT *reg, BIT in, BIT load, BIT *out) {
    BIT mo;
    mux(out, in, load, &mo);
    dff(reg, mo, out);
}

/*
CHIP Bit {
    IN in, load;
    OUT out;

    PARTS:
		Mux(a=do, b=in, sel=load, out=mo);
		DFF(in=mo, out=do);
		And(a=do, b=do, out=out);
}


CHIP Register {
    IN in[16], load;
    OUT out[16];

    PARTS:
    Bit(in=in[15], load=load, out=out[15]);
    Bit(in=in[14], load=load, out=out[14]);
    Bit(in=in[13], load=load, out=out[13]);
    Bit(in=in[12], load=load, out=out[12]);
    Bit(in=in[11], load=load, out=out[11]);
    Bit(in=in[10], load=load, out=out[10]);
    Bit(in=in[9],  load=load, out=out[9]);
    Bit(in=in[8],  load=load, out=out[8]);
    Bit(in=in[7],  load=load, out=out[7]);
    Bit(in=in[6],  load=load, out=out[6]);
    Bit(in=in[5],  load=load, out=out[5]);
    Bit(in=in[4],  load=load, out=out[4]);
    Bit(in=in[3],  load=load, out=out[3]);
    Bit(in=in[2],  load=load, out=out[2]);
    Bit(in=in[1],  load=load, out=out[1]);
    Bit(in=in[0],  load=load, out=out[0]);
}

bool posEdge(BIT s) {
    return s == 1;
}

BIT clock = 0;

void dff(BIT i, BIT *o) {
    BIT r;
    if (posEdge(clock)) r = i;
    *o = r;
}

void bit(BIT i, BIT load, BIT clock, BIT *o) {
    BIT din;
    mux(i, *o, load, &din);
    dff(din, o);
}
*/