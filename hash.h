#ifndef HASH_H
#define HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#define HASH_SIZE 100
#define MULTIPLIER 31


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

#endif
