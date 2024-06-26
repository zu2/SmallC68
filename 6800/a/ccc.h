**  SMALL-C HEADER FILE

        ORG $800
        OPT NOG

WARMS   EQU $AD03
exit    EQU $AD03
fclose  EQU $4
fopen   EQU $8
getc    EQU $C
getchar EQU $10
gets    EQU $14
putc    EQU $18
putchar EQU $1C
puts    EQU $20
RTSC    EQU $24
isalpha EQU $28
isdigit EQU $2C
isalnum EQU $30
islower EQU $34
isupper EQU $38
isspace EQU $3C
toupper EQU $40
tolower EQU $44
strclr  EQU $48
strlen  EQU $4C
strcpy  EQU $50
strcat  EQU $54
strcmp  EQU $58
EOF     EQU -1

*  This stuff has been added to implement command line
*    parameter passing ( argc, argv    stuff ).

        FCB 86   SWITCH TO INLINE CODE
        BRA zzSTRT BRANCH AROUND LOCAL STORAGE

zzARGC  RMB 2
zzXTMP  RMB 2 TEMP STORE FOR X REG
zzARGV  RMB 20  ARRAY OF POINTERS

NXTCH   EQU $AD27 NEXT CHARACTER ROUTINE

zzSTRT  CLR zzARGC
        CLR zzARGC+1
        INC zzARGC+1 SET TO AT LEAST 1 PARAMETER
        LDX #$A080 POINT TO LINE BUFFER
        STX zzARGV
        LDX $AC14 GET LINE POINTER
        DEX FIX UP
        CLR 0,X MARK END OF STRING
        LDX #zzARGV+2 NEXT ADDRESS POINTER
        LDA B #9 MAX # OF ARG'S - 1

* now get the rest of arguments

zzNEXT  JSR NXTCH GET NEXT CHAR FROM LINE BUFFER
        CMP A #$0D IS IT A CR ?
        BEQ zzDONE YES -- FINISHED
        CMP A $AC02 COMPARE TO E.O.L.
        BEQ zzDONE

        INC zzARGC+1 BUMP ARGUMENT COUNTER
        LDA A $AC14 LINE BUFFER POINTER MSB
        STA A 0,X SAVE IN POINTER ARRAY
        INX
        LDA A $AC15 LINE BUFFER POINTER LSB
        DEC A FIX ADDRESS
        STA A 0,X
        INX
        
zzAGAIN JSR NXTCH LETS GET TO END OF PARAMETER STRING
        CMP A #$0D
        BEQ zzDONE
        CMP A $AC02
        BEQ zzDONE
        CMP A #$20 BLANK ?
        BEQ zzMARK
        CMP A #',
        BNE zzAGAIN
zzMARK  STX zzXTMP SAVE POINTER
        LDX $AC14
        DEX
        CLR 0,X
        LDX zzXTMP
        DEC B DECREMENT MAX PARAM. COUNT
        BEQ zzDONE
        BRA zzNEXT

zzDONE  LDX $AC14
        CLR 0,X MARK THE FINAL STRING
*
*-------------------------------------------------------
*
        JSR RTSC RETURN TO INTERPRETED CODE

        FCB 2*2 LOAD VALUE
        FDB zzARGC
        FCB 2*10 PUSH ON STACK
        FCB 2*0 LOAD ADDRESS
        FDB zzARGV
        FCB 2*10 PUSH ON STACK
*
*------------------------------------------------------
*

*;/* ASMB c_source.a +SY # Asm. suppressing symbol table, listing */
*;/* Local Variables: */
*;/* mode:asm         */
*;/* End:             */
