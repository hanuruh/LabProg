#ifndef INSTR_H
#define INSTR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define HASH_SIZE 100
#define MULTIPLIER 31

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
Instr mkInstr(OpKind op, Elem x, Elem y, Elem z, int a, int b); 
Instr convertToInstruc(char*, int indice);
int getValue(Elem x);
int instrucType(char* str, char* ch); 
char* getName(Elem x);
void escrever(Instr intruc);
void removeSpaces(char *str);

#endif


