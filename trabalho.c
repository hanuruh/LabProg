#include "trabalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//a função run começa a reading do ficheiro
//primeiro testar os construtores
//depois fazer cena de passar ficheiro para lista, função strtoken ver

/*******************HASHTABLE**********************/
//Problema: insert ajuda em x = 2 pq recebe char & int, mas para x = y??
unsigned int hash(char *s){
		
unsigned int h;

unsigned char *p;

h=0;

for(p=(unsigned char *)s;*p!='\0';p++)
	h= MULTIPLIER *h + *p;
return h%HASH_SIZE;
}

//obter valor de STRING
PROG_CELL lookup(char *s){
	int index;
	PROG_CELL p;
	index= hash(s);
	for(p=table[index];p!=NULL;p=p->next){
		if(strcmp(s,p->chave)==0)
			return p;
	}
	return NULL;
}

//inserir o valor de eg. x = INT_CONST
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
/*******************HASHTABLE**********************/

//PROG 
Elem mkVar(char * s){
	Elem new;
	new.kind = STRING;
	new.content.name = strdup(s);
	return new;
}

Elem mkInt(int n){
	Elem new;
	new.kind = INT_CONST;
	new.content.val = n;
	return new;
}

Elem empty(){
	Elem new;
	new.kind = EMPTY;
	return new;
}

Instr mkInstr(Opkind oper, Elem x, Elem y, Elem z){
	Instr new;
	new.op = oper;
	new.first = x;
	new.second = y;
	new.third = z;
	return new;
}

PROG_LIST newList(Instr head, PROG_LIST tail_l){
	PROG_LIST new;
	new.elem = head;
	new.next = tail_l;
	return new;
}

int getValue(Elem x){
	if(x.kind = INT_CONST)
		return x.content.val;
}

char* getName(Elem x){
  if (x.kind == STRING) {
    return x.content.name;
  }
}

void printInstruc(Instr instruc){
	switch(instruc.first.kind){
		case INT_CONST:
			printf("%d\n", getVal(instruc.first); break;
		case STRING
			printf("%s\n", getName(instruc.first); break;
	}	
}

void escrever(Instr instruc){
	PROG_CELL C1;
	PROG_CELL C2;
	init_table(); //não sei muito bem onde pôr isto tbh
	switch(instruc.op){
		case PRINT:
			printInstrc(instruc);		
		case ATRIB:
			if (inst.second.kind == INT_CONST) {
				printf("%s = %d\n", getName(inst.first), getVal(inst.second));
				insert(inst.first,inst.second);
			} else if (inst.second.kind == STRING) {
				printf("%s = %s\n", getName(inst.first), getName(inst.second));
				//insert(inst.first,inst.second); não vai dar por insert tipo char & int, não char & char
			}
				break;
		case ADD:
			if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
				printf("%d\n",( getVal(inst.second) + getVal(inst.third) ));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == STRING) {
				C1 = lookup(inst.second);
				C2 = lookup(inst.third);
				printf("%d\n",( getValofCell(C1) + getValofCell(C2))); 
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
				C1 = lookup(inst.second);
				printf("%d\n", ( getValofCell(C1) +  getVal(inst.third));
				break;
			}
			if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
				C1 = lookup(inst.third);
				printf("%d\n", ( getValofCell(C1) +  getVal(inst.second));
				break;
			}
				break;
		case SUB:
			if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
				printf("%d\n",( getVal(inst.second) - getVal(inst.third) ));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == STRING) {
				C1 = lookup(inst.second);
				C2 = lookup(inst.third);
				printf("%d\n",( getValofCell(C1) - getValofCell(C2)));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
				C1 = lookup(inst.second);
				printf("%d\n", ( getValofCell(C1) -  getVal(inst.third));
				break;
			}
			if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
				C1 = lookup(inst.third);
				printf("%d\n", ( getValofCell(C1) -  getVal(inst.second));
				break;
			}
				break;
		case MUL:
			if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
				printf("%d\n",( getVal(inst.second) * getVal(inst.third) ));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == STRING) {
				C1 = lookup(inst.second);
				C2 = lookup(inst.third);
				printf("%d\n",( getValofCell(C1) * getValofCell(C2)));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
				C1 = lookup(inst.second);
				printf("%d\n", ( getValofCell(C1) *  getVal(inst.third));
				break;
			}
			if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
				C1 = lookup(inst.third);
				printf("%d\n", ( getValofCell(C1) *  getVal(inst.second));
				break;
			}
	}
}

void escreverDEBBUG(Instr inst) {
  switch (inst.op) {
    case ATRIB:
    if (inst.second.kind == INT_CONST) {
      printf("%s = %d\n", getName(inst.first), getVal(inst.second));
    } else if (inst.second.kind == STRING) {
      printf("%s = %s\n", getName(inst.first), getName(inst.second));

    }
    break;
    case ADD:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d + %d\n", getName(inst.first), getVal(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s + %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s + %d\n", getName(inst.first), getName(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d + %s\n", getName(inst.first), getVal(inst.second), getName(inst.third));
      break;
    }
    break;
    case SUB:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d - %d\n", getName(inst.first), getVal(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s - %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s - %d\n", getName(inst.first), getName(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d - %s\n", getName(inst.first), getVal(inst.second), getName(inst.third));
      break;
    }
    break;
    case MUL:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d * %d\n", getName(inst.first), getVal(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s * %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s * %d\n", getName(inst.first), getName(inst.second), getVal(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d * %s\n", getName(inst.first), getVal(inst.second), getName(inst.third));
      break;
    }
  }
}
