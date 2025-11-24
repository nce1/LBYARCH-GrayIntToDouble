; Nicole Almoradie S19B

section .data
    const DQ 255.0
    
section .text
default rel
bits 64
global imgCvtGrayIntToDouble
imgCvtGrayIntToDouble:    
    XOR R9, R9
    MOVSD XMM2, [const]
    
    L1:
    MOV RAX, [RDX]
    CVTSI2SD XMM1, RAX
    DIVSD XMM1, XMM2
    MOVSD [R8], XMM1
    ADD RDX, 8
    ADD R8, 8
    
    INC R9
    CMP RCX, R9
    JNZ L1  
    
    RET