#include "trabalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//a função run começa a reading do ficheiro
//primeiro testar os construtores
//depois fazer cena de passar ficheiro para lista, função strtoken ver
/*
Inserção dum valor para uma variável: para que o utilizador possa indicar um valor para a variável
identificada pela string referida na instrução. Caso a variável já tenha valor,
 esse valor será substituído pelo novo.
ler(<variável>);
*/
/*
 Atribuir o valor duma expressão a uma variável: todas as variáveis que ocorram na expressão deverão
 ter já um valor definido; o valor da expressão será atribuído à variável que se encontra 
 do lado esquerdo.
<variável> = <expressão>;
*/
//instruções goto: goto label
//Comandos condicionais da forma: if <variável> goto <label>
//Terminar a execução do programa: quit;


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

char* getNameofCell(PROG_CELL p){
	return p->chave;
}
/*******************HASHTABLE**********************/

/*******************LIST**********************/
PROG_LIST mkList(Instr head, PROG_LIST tail_l){
	PROG_LIST new;
	new.elem = head;
	new.next = tail_l;
	return new;
}

PROG_LIST append(PROG_LIST l1, PROG_LIST l2){
	PROG_LIST new = l1;
	if(l1 == NULL) return l2;
	else{
		while( l1 -> next != NULL)
			l1 = l1 -> next;
		l1 -> next = l2;
	}
	return new;	
}

PROG_LIST addLast(Instr n, PROG_LIST l1){
	PROG_LIST l2 = newList(n,NULL);
	PROG_LIST new = append(l1,l2);	
	return new;
}
/*******************LIST**********************/

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

Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z){
	Instr new;
	new.op = oper;
	new.first = x;
	new.second = y;
	new.third = z;
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
			printf("%d\n", getValue(instruc.first)); break;
		case STRING:
			printf("%s\n", getName(instruc.first)); break;
		default: printf("Erro de Impressão\n");
	}	
}

void escrever(Instr inst){
	//células que contêm valores de x e respetivo value (se existir)
	//C1 = lookup(x) C1 vai ter a célula de x
	//C1->elem delvolve valor de x (se existir)
	PROG_CELL C1; 
	PROG_CELL C2;
	init_table(); //não sei muito bem onde pôr isto tbh
	switch(inst.op){
		case PRINT:
			printInstruc(inst);		
		case ATRIB:
			if (inst.second.kind == INT_CONST) {
				printf("%s = %d\n", getName(inst.first), getValue(inst.second));
				insert(getName(inst.first),getValue(inst.second));
			} else if (inst.second.kind == STRING) {
				printf("%s = %s\n", getName(inst.first), getName(inst.second));
				//insert(inst.first,inst.second); não vai dar por insert tipo char & int, não char & char
			}
				break;
		case ADD:
			if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
				printf("%d\n",( getValue(inst.second) + getValue(inst.third) ));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == STRING) {
				C1 = lookup(getName(inst.second));
				C2 = lookup(getName(inst.third));
				printf("%d\n",( getValofCell(C1) + getValofCell(C2))); 
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
				C1 = lookup(getName(inst.second));
				printf("%d\n", ( getValofCell(C1) +  getValue(inst.third)));
				break;
			}
			if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
				C1 = lookup(getName(inst.third));
				printf("%d\n", ( getValofCell(C1) +  getValue(inst.second)));
				break;
			}
				break;
		case SUB:
			if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
				printf("%d\n",( getValue(inst.second) - getValue(inst.third) ));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == STRING) {
				C1 = lookup(getName(inst.second));
				C2 = lookup(getName(inst.third));
				printf("%d\n",( getValofCell(C1) - getValofCell(C2)));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
				C1 = lookup(getName(inst.second));
				printf("%d\n", ( getValofCell(C1) -  getValue(inst.third)));
				break;
			}
			if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
				C1 = lookup(getName(inst.third));
				printf("%d\n", ( getValofCell(C1) -  getValue(inst.second)));
				break;
			}
				break;
		case MUL:
			if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
				printf("%d\n",( getValue(inst.second) * getValue(inst.third) ));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == STRING) {
				C1 = lookup(getName(inst.second));
				C2 = lookup(getName(inst.third));
				printf("%d\n",( getValofCell(C1) * getValofCell(C2)));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
				C1 = lookup(getName(inst.second));
				printf("%d\n", ( getValofCell(C1) *  getValue(inst.third)));
				break;
			}
			if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
				C1 = lookup(getName(inst.third));
				printf("%d\n", ( getValofCell(C1) *  getValue(inst.second)));
				break;
			}
				break;
		case DIV:
			if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
				printf("%d\n",( getValue(inst.second) / getValue(inst.third) ));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == STRING) {
				C1 = lookup(getName(inst.second));
				C2 = lookup(getName(inst.third));
				printf("%d\n",( getValofCell(C1) / getValofCell(C2)));
				break;
			}
			if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
				C1 = lookup(getName(inst.second));
				printf("%d\n", ( getValofCell(C1) /  getValue(inst.third)));
				break;
			}
			if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
				C1 = lookup(getName(inst.third));
				printf("%d\n", ( getValofCell(C1) /  getValue(inst.second)));
				break;
			}
		default: 
			printf("Erro!!\n");
	}
}

void escreverDEBBUG(Instr inst) {
  switch (inst.op) {
    case ATRIB:
    if (inst.second.kind == INT_CONST) {
      printf("%s = %d\n", getName(inst.first), getValue(inst.second));
    } else if (inst.second.kind == STRING) {
      printf("%s = %s\n", getName(inst.first), getName(inst.second));

    }
    break;
    case ADD:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d + %d\n", getName(inst.first), getValue(inst.second), getValue(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s + %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s + %d\n", getName(inst.first), getName(inst.second), getValue(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d + %s\n", getName(inst.first), getValue(inst.second), getName(inst.third));
      break;
    }
    break;
    case SUB:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d - %d\n", getName(inst.first), getValue(inst.second), getValue(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s - %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s - %d\n", getName(inst.first), getName(inst.second), getValue(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d - %s\n", getName(inst.first), getValue(inst.second), getName(inst.third));
      break;
    }
    break;
    case MUL:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d * %d\n", getName(inst.first), getValue(inst.second), getValue(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s * %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s * %d\n", getName(inst.first), getName(inst.second), getValue(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d * %s\n", getName(inst.first), getValue(inst.second), getName(inst.third));
      break;
    }
    
    default: 
		printf("Erro!!\n");
  }
}
