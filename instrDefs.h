#ifndef INSTR_DEFS_H
#define INSTR_DEFS_H

//Command opcodes
#define OPCODE 0xF0000000
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define SR 4
#define LR 5
#define PRINT 6
#define LI 7
#define JR 8
#define JMP 9
#define MOV 10
#define BEQ 11
#define BNE 12
#define BLT 13
#define BGT 14
#define HALT 15

#ifdef DEBUG
	#define DSTAT(VAR) cout << VAR  << "\n";
#else
	#define DSTAT(VAR) 
#endif

typedef struct inst_thrOP
{
	unsigned short op : 4;
	unsigned short opda : 5;
	unsigned short opdb : 5;
	unsigned short sto : 5;
	unsigned short fa : 1;
	unsigned short fb : 1;
	unsigned short pad : 10;
}instrHOP;

//Three operand bitmasks
#define H_OPDA 0xF8000000
#define H_OPDB 0x7C00000
#define H_STO  0x3E0000
#define H_FA   0x10000
#define H_FB   0x8000

//For two operand commands, the second longer operand:
#define T_OPDB 0x7FFFFF

typedef struct instr_twoOP
{
	unsigned short op : 4;
	unsigned short opda : 5;
	unsigned int opdb : 23;
}instrTOP;



typedef struct jumpInstr
{
	unsigned short op : 4;
	unsigned short opt : 1;
	unsigned int val : 27;
}jumpInstr;

typedef union instr
{
	jumpInstr j;
	instrTOP t;
	instrHOP h;
	int ival;
}instr;


#endif
