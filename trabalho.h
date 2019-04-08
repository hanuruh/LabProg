#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define HASH_SIZE 100
#define MULTIPLIER 31

/*******************PROG_FUNC**********************/
typedef enum {ATRIB, ADD, SUB, MUL, DIV, IF, PRINT, READ, GOTO, LABEL,START,QUIT} OpKind;

typedef enum {EMPTY, INT_CONST, STRING} ElemKind;


typedef struct{
     ElemKind kind;
		union{ 
           int val;
           char *name;
        } content;
}Elem;

typedef struct{
     OpKind op;
     Elem first, second, third;
     int tipo, indice;
} Instr;

Elem mkVar(char *s);
Elem mkInt(int n);
Elem empty();
Instr mkInstr(OpKind op, Elem x, Elem y, Elem z, int a, int b); //exemplo k = (mkInstr(ADD,mkVar("x"),mkVar("y"),mkInt(2)); y = x + 2 . k vai representar e memoria a instrução
Instr convertToInstruc(char*, int indice);
int getValue(Elem x);
int instrucType(char* str, char* ch); 
char* getName(Elem x);
void escrever(Instr intruc);
void removeSpaces(char *str);
/*******************PROG_FUNC**********************/

/*******************LIST**********************/
typedef struct list{ 
	Instr elem;
	struct list *next;
}*PROG_LIST;

PROG_LIST newList(Instr head, PROG_LIST tail);
PROG_LIST tail(PROG_LIST l);
PROG_LIST addLast(Instr n, PROG_LIST l1);
PROG_LIST append(PROG_LIST l1, PROG_LIST l2);
Instr head(PROG_LIST l);
int length(PROG_LIST l);
int getIndex(char* s, PROG_LIST lista);
void printList(PROG_LIST l);
int run(PROG_LIST l);
/*******************LIST**********************/

/*******************HASHTABLE**********************/
typedef struct hash{
	char *chave;	
	int elem;
	struct hash *next;
}*PROG_CELL;

unsigned int hash(char *s);

PROG_CELL table[HASH_SIZE];
PROG_CELL lookup(char *s);
void insert(char *s, int value);
void init_table();
void PrintCell(PROG_CELL c);
int getValofCell(PROG_CELL p);
char* getNameofCell(PROG_CELL p);
/*******************HASHTABLE**********************/



