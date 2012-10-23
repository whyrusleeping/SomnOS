#ifndef INSTR_DEFS_H
#define INSTR_DEFS_H

//Command opcodes
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3


#define PRINTN 6
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
	unsigned short pad : 13;
}instrHOP;

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
