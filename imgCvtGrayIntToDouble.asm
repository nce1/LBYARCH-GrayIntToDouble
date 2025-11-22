; Nicole Almoradie S19B

section .data
    const DQ 255.0
    
section .text
default rel
bits 64
global imgCvtGrayIntToDouble
imgCvtGrayIntToDouble:
    XOR R8, R8
    
    L1:
    MOV RAX, [RDX]
    CVTSI2SD XMM1, RAX 
    DIVSD XMM1, [const]
    MOVSD [RDX], XMM1
    ADD RDX, 8
    
    INC R8
    CMP RCX, R8
    JNZ L1  
    
    RET