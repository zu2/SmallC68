/*      >>>>>> start of cc8 <<<<<<<     */

/* Begin a comment line for the assembler */
comment()
{       outbyte('*');
}

/* Put out assembler info before any code is generated */
header()
{       comment();
        outstr(BANNER);
        nl();
        comment();
        outstr(VERSION);
        nl();
        comment();
        outstr(AUTHOR);
        nl();
        comment();
        nl();
        if(mainflg){            /* do stuff needed for first */
                ol("LIB CCC.H"); /* assembler file */

                zcall("main");  /* call the code generated by small-c */
                pseudoins(43); ol("JMP WARMS");
                }
}
/* Print any assembler stuff needed after all code */
trailer()
{       ol("END");

        nl();
        comment();
        outstr(" --- End of Compilation ---");
        nl();
}

/* Fetch a static memory cell into the primary register */
getmem(sym)
        char *sym;
{       if((sym[IDENT]!=POINTER)&(sym[TYPE]==CCHAR))
                pseudoins(3);
        else
                pseudoins(2);
        defword(); outstr(sym+NAME); nl();
        }
/* Fetch the address of the specified symbol */
/*      into the primary register */
getloc(sym)
        char *sym;
{       pseudoins(1); defword();
        outdec((sym[OFFSET]&255)*256+(sym[OFFSET+1]&255)-Zsp);
        nl();
        }
/* Store the primary register into the specified */
/*      static memory cell */
putmem(sym)
        char *sym;
{       if((sym[IDENT]!=POINTER)&(sym[TYPE]==CCHAR))
                pseudoins(7);
        else 
                pseudoins(6);
        defword();
        outstr(sym+NAME);
        nl();
        }
/* Store the specified object type in the primary register */
/*      at the address on the top of the stack */
putstk(typeobj)
        char typeobj;
{       zpop();
        if(typeobj==CCHAR) pseudoins(9);
                else pseudoins(8);
        }
/* Fetch the specified object type indirect through the */
/*      primary register into the primary register  */
indirect(typeobj)
        char typeobj;
{       if(typeobj==CCHAR) pseudoins(5);
                else pseudoins(4);
}
/* Print partial instruction to get an immediate value */
/*      into the primary register */
immed()
{       pseudoins(0); defword();
        }
/* Push the primary register onto the stack */
zpush()
{       pseudoins(10);
        Zsp=Zsp-2;
}
/* Pop the top of the stack  */
zpop()
{       Zsp=Zsp+2;
}
/* Swap the primary register and the top of the stack */
swapstk()
{       pseudoins(11);
        }
/* Call the specified subroutine name */
zcall(sname)
        char *sname;
{       pseudoins(14); defword();
        outstr(sname);
        nl();
}

/* Return from subroutine */
zret()
{       pseudoins(16);
}
/* Perform subroutine call to value on top of stack */
callstk()
{       pseudoins(15);
        Zsp=Zsp-2;
        }
/* Jump to specified internal label number */
jump(label)
        int label;
{       pseudoins(12); defword();
        printlabel(label);
        nl();
        }
/* Test the primary register and jump if false to label */
testjump(label)
        int label;
{       pseudoins(13); defword();
        printlabel(label);
        nl();
        }
/* Print a pseudo-instruction for interpreter  */
pseudoins(k)
        int k;
{       defbyte();
        outdec(k+k); nl();
        }
/* Print pseudo-op to define a byte */
defbyte()
{       ot("FCB ");
}
/*Print pseudo-op to define storage */
defstorage()
{       ot("RMB ");
}
/* Print pseudo-op to define a word */
defword()
{       ot("FDB ");
}
/* Modify the stack pointer to the new value indicated */
modstk(newsp)
        int newsp;
 {      int k;
        k=newsp-Zsp;
        if(k==0) return(newsp);
        pseudoins(17); defword();
        outdec(k); nl();
        return (newsp);
}
/* Double the primary register */
doublereg()
{       pseudoins(18);
        }
/* Add the primary and top of stack (pop) */
/*      (results in primary) */
zadd()
{       pseudoins(19);
        }
/* Subtract the primary register from the top of stack */
/*      (results in primary) */
zsub()
{       pseudoins(20);
        }
/* Multiply the primary register and top of stack */
/*      (results in primary */
mult()
{       pseudoins(21);
        }
/* Divide the top of stack by the primary register */
/*      (quotient in primary) */
div()
{       pseudoins(22);
        }
/* Compute remainder (mod) of top of stack divided */
/*      by the primary */
/*      (remainder in primary)  */
zmod()
{       pseudoins(23);
        }
/* Inclusive 'or' the primary and the top of stack */
/*      (results in primary) */
zor()
{       pseudoins(24);
        }
/* Exclusive 'or' the primary and the top of stack */
/*      (results in primary) */
zxor()
{       pseudoins(25);
        }
/* 'And' the primary and the top of stack */
/*      (results in primary) */
zand()
{       pseudoins(26);
        }
/* Arithmetic shift right the top of stack number of */
/*      times in primary (results in primary) */
asr()
{       pseudoins(27);
        }
/* Arithmetic left shift the top of stack number of */
/*      times in primary (results in primary) */
asl()
{       pseudoins(28);
        }
/* Form two's complement of primary register */
neg()
{       pseudoins(29);
        }
/* Form one's complement of primary register */
com()
{       pseudoins(30);
        }
/* Increment the primary register by one */
inc()
{       pseudoins(31);
        }
/* Decrement the primary register by one */
dec()
{       pseudoins(32);
        }

/* Following are the conditional operators */
/* They compare the top of the stack against the primary */
/* and put a literal 1 in the primary if the condition is */
/* true, otherwise they clear the primary register */

/* Test for equal */
zeq()
{       pseudoins(33);
        }
/* Test for not equal */
zne()
{       pseudoins(34);
        }
/* Test for less than (signed) */
zlt()
{       pseudoins(35);
        }
/* Test for less than or equal to (signed) */
zle()
{       pseudoins(36);
        }
/* Test for greater than (signed) */
zgt()
{       pseudoins(37);
        }
/* Test for greater than or equal to (signed) */
zge()
{       pseudoins(38);
        }
/* Test for less than (unsigned) */
ult()
{       pseudoins(39);
        }
/* Test for less than or equal to (unsigned) */
ule()
{       pseudoins(40);
        }
/* Test for greater than (unsigned) */
ugt()
{       pseudoins(41);
        }
/* Test for greater than or equal to (unsigned) */
uge()
{       pseudoins(42);
        }

#asm
*   This stuff is recoded in Assembler to speed things up
*
*       Test if given char is alpha     *
* alpha(c)
*       char c;
* {     c=c&127;
*       return(((c>='a')&(c<='z'))|
*               ((c>='A')&(c<='Z'))|
*               (c='_'));
* }
*
alpha EQU isalpha
*
*       Test if given char is numeric   *
*
* numeric(c)
*       char c;
* {     c=c&127;
*       return((c>='0')&(c<='9'));
* }
*
numeric EQU isdigit
*
*       Test if given char is alphanumeric      *
*
* an(c)
*       char c;
* {     return((alpha(c)|(numeric(c)));
* }
*
an EQU isalnum
*
*
* ch()
* {     return(line[lptr]&127); }
*
ch      FCB     86      switch to assembly
        CLR A
        LDX     #line
        LDA B   lptr+1
        STA B   chXXX+1
chXXX   LDA B   0,X     self modifying code !!!!
        AND B   #$7F
        JMP     RTSC
*
* nch()
* {     if(ch()==0)return(0);
*               else return(line[lptr+1]&127);
* }
*
nch     FCB     86
        CLR A
        LDX     #line
        LDA B   lptr+1
        STA B   nchXXX+1
        INC B
        STA B   nchYYY+1
nchXXX  LDA B   0,X     self modifying code !!!!
        AND B   #$7F
        BNE     nchYYY
        JMP     RTSC
nchYYY  LDA B   0,X     self modifying code !!!!
        AND B   #$7F
        JMP     RTSC
*
* gch()
* {     if(ch()==0)return(0);
*               else return(line[lptr++]&127);
* }
*
gch     FCB     86
        CLR A
        LDX     #line
        LDA B   lptr+1
        STA B   gchXXX+1
gchXXX  LDA B   0,X     self modifying code !!!!
        AND B   #$7F
        BEQ     gchYYY
        INC     lptr+1  bump the pointer
gchYYY  JMP     RTSC
*
*  direct output to console   *
*
* toconsole()
* {     saveout=output;
*       output=0;       }
*
toconsole FCB   86
        LDX     output
        STX     saveout
        CLR     output
        CLR     output+1
        JMP     RTSC
*
*  direct output back to file   *
*
* tofile()
* {     if(saveout)
*               output=saveout;
*       saveout=0;      }
*
tofile  FCB     86
        LDX     saveout
        BEQ     *+5
        STX     output
        CLR     saveout
        CLR     saveout+1
        JMP     RTSC
*
**************************
*  Compare two strings:  if equal return length,  else NULL
*
* streq(str1,str2)
*       char str1[], str2[];
*{      int k;
*       k=0;
*       while (str2[k])
*               {if ((str1[k])!=(str2[k])) return 0;
*               k++;
*               }
*       return k;
* }
*
streq   FCB     86      switch to assembly
        TSX             point to data
        LDX     4,X     pointer to str1
        STX     stX1    save
        CLR A           preset NULL
        CLR B
        PSH A
        TSX
        LDX     3,X     pointer to str2
*
stLooP  LDA A   0,X     get char from str2
        BEQ     stRETR  if NULL then done
        INX
        STX     stX2
        LDX     stX1    pointer to str1
        CMP A   0,X     compare chars
        BNE     stRET0  if not same return NULL
        INX
        STX     stX1
        LDX     stX2    point to str2
        ADD B   #1      increment count
        BCC     stLooP  check for overflow
        PUL A
        INC A           adjust MSB'S
        PSH A
        BRA     stLooP
*
stRETR  PUL A           return length of string
        JMP     RTSC
*
stRET0  INS             clean stack
        CLR A           return NULL
        CLR B
        JMP     RTSC    back to interpreter
*
stX1    FDB     0
stX2    FDB     0
*
*****************************************************
*   compare strings of a given length
*
* astreq(str1,str2,len)
*       char str1[], str2[]; int len;
* {
*       int k;
*       k=0;
*       while (k<len)
*               { if ((str1[k])!=(str2[k])) break;
*               if (str1[k]==0) break;
*               if (str2[k]==0) break;  /*  seems and is redundant !!!! */
*               k++;
*               }
*       return k;
* }
*
astreq  FCB     86
        TSX
        LDX     4,X     point to str2
        STX     stX2
        TSX
        LDX     6,X     point to str1
        STX     stX1
        TSX
        LDX     2,X     get len
        CLR A           preset NULL
        CLR B
        PSH A
        INX
*
astrLP  DEX
        BEQ     astrBR  end of loop ?
        STX     astrLN  save counter
        LDX     stX1
        LDA A   0,X     get char from str1
        BEQ     astrBR  NULL ?
        LDX     stX2
        CMP A   0,X     compare to str2
        BNE     astrBR  exit on inequality
        INX
        STX     stX2
        LDX     stX1
        INX
        STX     stX1
        LDX     astrLN
        ADD B   #1      bump length counter
        BCC     astrLP
        PUL A
        INC A
        PSH A
        BRA     astrLP
*
astrBR  PSH B           save length
        LDX     stX1
        LDA B   0,X     get str1 char
        JSR     alPHA
        PSH B           save result
        LDA B   0,X
        JSR     nuMERIC
        TSX
        ORA B   0,X     set an() flag
        INS             clear stack
        BNE     astrR0  if set, return NULL
        LDX     stX2
        LDA B   0,X     get str2 char
        JSR     alPHA
        PSH B
        LDA B   0,X
        JSR     nuMERIC
        TSX
        ORA B   0,X     set an() flag
        INS
        BNE     astrR0
*
        PUL B           return length count
        PUL A
        JMP     RTSC
*
astrR0  INS             clean stack
        INS
        CLR A           return NULL
        CLR B
        JMP     RTSC
*
astrLN  FDB     0
*
*
*
alPHA   CLR A
        AND B   #$7F
        CMP B   #'a
        BLT     alPHA1
        CMP B   #'z
        BLE     alYES
alPHA1  CMP B   #'A
        BLT     alPHA2
        CMP B   #'Z
        BLE     alYES
alPHA2  CMP B   #'_
        BEQ     alYES
*
alNO    CLR B
        RTS
*
alYES   LDA B   #1
        RTS
*
*
nuMERIC CLR A
        AND B   #$7F
        CMP B   #'0
        BLT     alNO
        CMP B   #'9
        BLE     alYES
        BRA     alNO
#endasm
/*     <<<<< End of Small-C compiler >>>>>      */
