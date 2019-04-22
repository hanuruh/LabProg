#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

unsigned int hash(char *s){
		
unsigned int h;

unsigned char *p;

h=0;

for(p=(unsigned char *)s;*p!='\0';p++)
	h= MULTIPLIER *h + *p;
return h%HASH_SIZE;
}

PROG_CELL lookup(char *s){
	int index = hash(s);
  while (table[index] != NULL) {
    if (table[index]->chave) {
      return table[index];
    }
    index ++;
    index %= HASH_SIZE;
  }
  return NULL;
}

void insert(char *s, int value){
	int index;
	index = hash(s);
	PROG_CELL p;
	p=(PROG_CELL)malloc(sizeof(struct list));
	p->chave= s;
	p->elem = value;
	p->next = table[index];	
	table[index] = p;
	
}

void init_table(){
	int index;
	for(index=0;index<HASH_SIZE;index++)
		table[index]=NULL;	
}

int getValofCell(PROG_CELL p){
	return p->elem;
}

char* getNameofCell(PROG_CELL p){
	return p->chave;
}
