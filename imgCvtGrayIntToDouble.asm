; Nicole Almoradie S19B

section .data
    const DQ 255.0
    
section .text
default rel
bits 64
global imgCvtGrayIntToDouble
imgCvtGrayIntToDouble:
    IMUL RDX, RCX
    XOR RCX, RCX
    
    L1:
    MOV EAX, [R8]
    CVTSI2SD XMM1, EAX 
    DIVSD XMM1, [const]
    MOVSD [R9], XMM1
    ADD R8, 4
    ADD R9, 8
        
    INC RCX
    CMP RCX, RDX
    JNZ L1  
    
    RET