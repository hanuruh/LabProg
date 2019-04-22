#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "instr.h"

#define HASH_SIZE 100
#define MULTIPLIER 31

typedef struct list{ 
	Instr elem;
	struct list *next;
}*PROG_LIST;

PROG_LIST newList(Instr head, PROG_LIST tail);
PROG_LIST tail(PROG_LIST l);
PROG_LIST addLast(Instr n, PROG_LIST l1);
PROG_LIST append(PROG_LIST l1, PROG_LIST l2);
PROG_LIST last(PROG_LIST l);
PROG_LIST file_to_list(char file_name[]);
Instr head(PROG_LIST l);
int length(PROG_LIST l);
int getIndex(char* s, PROG_LIST lista);
void printList(PROG_LIST l);

#endif
