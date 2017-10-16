// ============= Chapter 5 ==================

void screen(WORD r[8*K], BIT in[16], BIT load, BIT address[13], BIT out) {
//    ram8K(r, in, load, address, out);
}

void keyboard(WORD r[1], BIT out[16]) {
    BIT in[16];
    if (_kbhit()) *r = _getch();
    reg(r, in, 0, out);
//    BIT in[16], load;
//    reg(r, in, load, out);
}

void memory(WORD r[12*K+1], BIT in[16], BIT load, BIT address[15], BIT out[16]) {
    BIT N14, Mload, Sload, outM[16], outS[16], outK[16];
    not(address[14], &N14);
    and(N14, load, &Mload);
    and(address[14], load, &Sload);
    ram16K(r, in, Mload, address, outM);
    screen(r, in, Sload, address, outS);
    keyboard(&r[12*K], outK);
}

void cpu(BIT inM[16], BIT instruction[16], BIT reset,
         BIT outM[16], BIT writeM, BIT addressM[15], BIT _pc[15]) {
    BIT ng, zr, g, ngzr, passLT, passEQ, passGT, passLE, pass;
    BIT Aout[16], AorM[16], Dout[16], ALUout[16], Ain[16];
    BIT Ainstruction, AluToA, Aload, PCload, Dload;
    or(ng, zr, &ngzr);
    not(ngzr, &g);
    and(ng, instruction[2], &passLT);
    and(zr, instruction[1], &passEQ);
    and(g,  instruction[0], &passGT);
    or(passLT, passEQ, &passLE);
    or(passLE, passGT, &pass);
    and(instruction[15], pass, &PCload);
    mux16(Aout, inM, instruction[12], AorM);
    alu(Dout, AorM, instruction[11], instruction[10], instruction[9],
        instruction[8], instruction[7], instruction[6], ALUout, &zr, &ng);
    pc(PC, Aout, PCload, 1, reset, _pc);
//    void pc(WORD r[1], BIT in[16], BIT load, BIT inc, BIT reset, BIT out[16]) {
//        BIT loadInc, loadIncReset, if1[16], if2[16], if3[16], o[16], oInc[16];
    
    not(instruction[15], &Ainstruction);
    and(instruction[15], instruction[5], &AluToA); // AluToA = I[15]&d1
    or(Ainstruction, AluToA, &Aload);
    mux16(instruction, ALUout, AluToA, Ain);
    reg(A, Ain, Aload, Aout);
    and(instruction[15], instruction[4], &Dload);
    reg(D, ALUout, Dload, Dout);
    and16(Aout, Aout, addressM);
    and(instruction[15], instruction[3], &writeM);
    and16(ALUout, ALUout, outM);
}

/*
		And16(a=Aout, b=Aout, out[0..14]=addressM);
		And(a=instruction[15], b=instruction[3], out=writeM); // writeM = I[15] & d3
		And16(a=ALUout, b=ALUout, out=outM);
}

CHIP Computer {
    IN reset;
		
    PARTS:
		
		Memory(in=inM, load=loadM, address=addressM, out=outM);
    ROM32K(address=pc, out=instruction);
		CPU(inM=outM, instruction=instruction, reset=reset, outM=inM, writeM=loadM, addressM=addressM, pc=pc);
}
*/