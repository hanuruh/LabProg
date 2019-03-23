#include "trabalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	return y;
}

Instr mkInstr(Opkind oper, Elem x, Elem y, Elem z){
	Instr new;
	new.op = oper;
	new.first = x;
	new.second = y;
	new.third = z;
	return new;
}

PROG_LIST newList(Instr head, PROG_LIST head_l){
	PROG_LIST new;
	new.elem = head;
	new.next = head_l;
	return new;
}

int getValue(Elem x){
	if(x.kind = INT_CONST)
		return x.val;
	else if(x.kind = STRING)//to continue...
		return 
}

void escrever(Instr instruc){
	switch(instruc.op){
		case ATRIB:
			if(instruc.second.kind == INT_CONST)
				printf("%s = %d", instruc.first, instruc.second);
			else if(instruc.second.kind == STRING)
				printf("%s = %s", instruc.first, instruc.second);
		case ADD:
			
			
			
	
	}


}
