// ============= Chapter 5 ==================

void screen(WORD r[8*K], BIT in[16], BIT load, BIT address[13], BIT out) {
//    ram8K(r, in, load, address, out);
}

void keyboard(WORD r[1], BIT out[16]) {
    BIT in[16];
    if (_kbhit()) *r = _getch();
    reg(r, in, 0, out);
}

void memory(WORD r[24*K+1], BIT in[16], BIT load, BIT address[15], BIT out[16]) {
    BIT N14, Mload, Sload, outM[16], outS[16], outK[16];
    not(address[14], &N14);
    and(N14, load, &Mload);
    and(address[14], load, &Sload);
//    printf("  memory:address=%04hx N14=%d Mload=%d Sload=%d\n", bits2int(address, 15), N14, Mload, Sload);
    ram16K(r, in, Mload, address, outM);
//    printf("  ram16K:in=%04hx outM=%04hx", bits2int(in, 16), bits2int(outM, 16));
    screen(&r[16*K], in, Sload, address, outS);
//    printf("  screen:address=%04hx N14=%d Mload=%d Sload=%d\n", bits2int(address, 15), N14, Mload, Sload);
    keyboard(&r[24*K], outK);
//    printf("  keyboard:address=%04hx N14=%d Mload=%d Sload=%d\n", bits2int(address, 15), N14, Mload, Sload);
}

void cpu(BIT inM[16], BIT instruction[16], BIT reset,
         BIT outM[16], BIT writeM, BIT addressM[15], BIT outPc[15]) { // BIT addressM[15], BIT outPc[15]
//  outM, instruction, reset, inM, loadM, addressM, outPc
    BIT ng, zr, g, ngzr, passLT, passEQ, passGT, passLE, pass;
    BIT Aout[16], AorM[16], Dout[16], ALUout[16], Ain[16];
    BIT Ainstruction, AluToA, Aload, PCload, Dload;

    printf("  instruction=%04hx\n", bits2int(instruction, 16));
    // JUMP condition
    or(ng, zr, &ngzr);
    not(ngzr, &g);
    and(ng, instruction[2], &passLT);
    and(zr, instruction[1], &passEQ);
    and(g,  instruction[0], &passGT);
    or(passLT, passEQ, &passLE);
    or(passLE, passGT, &pass);
    and(instruction[15], pass, &PCload);
    mux16(Aout, inM, instruction[12], AorM);

    // ALU
    alu(Dout, AorM, instruction[11], instruction[10], instruction[9],
        instruction[8], instruction[7], instruction[6], ALUout, &zr, &ng);
    printf("  ALUout=%04hx zr=%x ng=%x\n", bits2int(ALUout, 16), zr, ng);

    // PC
    printf("  PC=%04hx Aout=%04hx PCload=%d reset=%d outPc=%04hx\n", *PC, bits2int(Aout, 16), PCload, reset, bits2int(outPc, 15));
    pc(PC, Aout, PCload, 1, reset, outPc);

    // A register
    not(instruction[15], &Ainstruction);
    and(instruction[15], instruction[5], &AluToA); // AluToA = I[15]&d1
    or(Ainstruction, AluToA, &Aload);
    mux16(instruction, ALUout, AluToA, Ain);
    reg(A, Ain, Aload, Aout);

    and16(Aout, Aout, addressM);
    printf("  A=%04hx Ain=%04hx Aload=%x Aout=%04hx addressM=%04hx\n", *A, bits2int(Ain, 16), Aload, bits2int(Aout, 16), bits2int(addressM, 15));

    // D register
    and(instruction[15], instruction[4], &Dload);
    
    reg(D, ALUout, Dload, Dout);

    // Output
    and(instruction[15], instruction[3], &writeM);
    and16(ALUout, ALUout, outM);
}

// 這裡必須用全域變數，因為有迴路！ rom32K => instructiion => cpu => outPc => rom32K
BIT inM[16], loadM, addressM[15], outM[16], outPc[15], instruction[16];

void computer(BIT reset) {
    rom32K(ROM, outPc, instruction);
    printf("  rom32k:outPc=%04hx instruction=%04hx\n", bits2int(outPc, 15), bits2int(instruction, 16));
    cpu(outM, instruction, reset, inM, loadM, addressM, outPc);
    //    printf("cpu:outM=%04hx instructon=%04hx reset=%x inM=%04hx loadM=%x addressM=%04hx outPc=%04hx\n", 
    //      bits2int(outM,16), bits2int(instruction, 16), reset, bits2int(inM,16), loadM, bits2int(addressM,15), bits2int(outPc,16));
    memory(MEMORY, inM, loadM, addressM, outM);
    printf("  memory: addressM=%04hx, outM=%04hx\n", bits2int(addressM, 15), bits2int(outM, 16));
}
