MOV DPTR, #1000
MOV R0, #0FFh
MOV R1, #01h
BCL_Bouclage :
    BCL1 :
        CLR A
        MOVC A, @DPTR
        INC DPTR
        MOV R1, DPH
        MOV R2, DPL
        MOV DPTR, DPTR+2FFFH
        MOVX @DPTR, A
        MOV DPH, R1
        MOV DPL, R2
        DJNZ R0, BCL1
    DJNZ R1, BCL_Bouclage