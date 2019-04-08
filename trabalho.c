#include "trabalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*******************HASHTABLE**********************/
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
	//printf("Insert");
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
PROG_LIST newList(Instr head, PROG_LIST tail_l){
	PROG_LIST new = malloc(sizeof(struct list));
	new->elem = head;
	new->next = tail_l;
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

PROG_LIST tail(PROG_LIST l){
	return(l->next);
}

Instr head(PROG_LIST l){
	if(l != NULL)
		return(l -> elem);
}

int length(PROG_LIST l){
	if(l==NULL) return 0;
	else return(1 + length(tail(l)));
}

void printList(PROG_LIST l) {
  while (l != NULL) {
    escrever(head(l));
    l = l->next;
  }
}

int getIndex(char* s, PROG_LIST lista){
	Instr instruc;
	while(lista != NULL){
		instruc = head(lista);
		if(instruc.op == LABEL){
			if(strcmp(s,getName(instruc.first))==0)
				return instruc.indice;
		}
		lista = lista->next;
	}
	return 0;
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

Instr mkInstr(OpKind oper, Elem x, Elem y, Elem z, int tipo, int indice){
	Instr new;
	new.op = oper;
	new.first = x;
	new.second = y;
	new.third = z;
	new.tipo = tipo;
	new.indice = indice;
	return new;
}

int getValue(Elem x){
		return x.content.val;
}

char* getName(Elem x){
    return x.content.name;
}

void removeSpaces(char* str){
	str[strlen(str)-2] = '\0';
	int count = 0, i;
	for(i=0; str[i]; i++)
		if(str[i] != ' ')
			str[count++] = str[i];
	str[count] = '\0';	
	//printf("%s\n",str);
}

//Saber o tipo de instruções
//Muito util para operações aritmétricas 
//Tipo 1 = str str
//Tipo 2 = int int
//Tipo 3 = str int
//Tipo 4 = int str
int instrucType(char* str, char* ch){
	char *save, *string, *var1, *var2, *type1, *type2;
	int temp1, temp2, tipo;
	
	string = strdup(str);
	if(string == NULL)
		return -1;
	
	save = strsep(&string, "=");
	save = strsep(&string, "=");
	type1 = strdup(save);
	type2 = strdup(save);
	
	var1 = strsep(&type1, ch);
	if((var1[0] >= 0x60 && var1[0] <= 0x7B)){ //detetar str
		var1 = strsep(&type1, ch);
		if((var1[0] >= 0x61 && var1[0] <= 0x7A)){ //str str
			tipo = 1;
			return tipo;
		}else{ //str int
			tipo = 3;
			return tipo;
		}
	}
	
	var2 = strsep(&type2, ch);
	if(!(var2[0] >= 0x60 && var2[0] <= 0x7B)){ //detetar int
		var2 = strsep(&type2, ch);
		if(!(var2[0] >= 0x61 && var2[0] <= 0x7A)){ //int int
			tipo = 2;
			return tipo;
		}else{ //int str
			tipo = 4;
			return tipo;
		}
	}
	return 0;
}

Instr convertToInstruc(char* s, int indice){
	Instr instruc;
	Elem elem1, elem2, elem3, ch, var, num, label;
	int index;
	//QUIT
	if(strstr(s,"quit") != NULL){
		instruc = mkInstr(QUIT,empty(),empty(),empty(),0,indice);
		return instruc;
	}
	//READ ler(x)
	else if(strstr(s,"ler") != NULL){
		char* string = strdup(s);
		char* aux = strsep(&string, "("); 
		aux = strsep(&string, ")");
		ch = mkVar(aux);
		instruc = mkInstr(READ,ch,empty(),empty(),0,indice);
		return instruc;
	}
	//PRINT escrever(x)
	else if(strstr(s,"escrever") != NULL){
		char* string = strdup(s);
		char* aux = strsep(&string, "(");
		aux = strsep(&string, ")");
		ch = mkVar(aux);
		instruc = mkInstr(PRINT,ch, empty(),empty(),0,indice);
		return instruc;
	}
	//IF if x goto  L1;
	else if(strstr(s,"if") != NULL && strstr(s,"goto") != NULL){
		char* string = strdup(s);
		char* aux = strsep(&string, "f");
		aux = strsep(&string, "g");
		//printf("if: %s\n", aux);
		ch = mkVar(aux);
		aux = strsep(&string, "o");
		aux = strsep(&string, "o");
		aux = strsep(&string, ";");
		//printf("if: %s\n", aux);
		label = mkVar(aux);
		instruc = mkInstr(IF,ch,label,empty(),0,indice);
		return instruc;
	}
	//GOTO 
	else if(strstr(s,"goto") != NULL){
		char* string = strdup(s);
		char* aux = strsep(&string, "o");
		aux = strsep(&string, "o");
		aux = strsep(&string, ";");
		ch = mkVar(aux);
		//printf("goto: %s\n", aux);
		instruc = mkInstr(GOTO,ch,empty(),empty(),0,indice);
		return instruc;
	}
	//LABEL
	else if(strstr(s,"label") != NULL) {
		char* string = strdup(s);
		char* aux = strsep(&string, "e");
		aux = strsep(&string, "l");
		aux = strsep(&string, ";");
		//printf("label: %s\n", aux);
		ch = mkVar(aux);
		instruc = mkInstr(LABEL,ch,empty(),empty(),0,indice);
		return instruc;
	}
	//ATRIB x = 2
	else if(strstr(s,"+") == NULL && strstr(s,"-") == NULL && strstr(s,"*") == NULL && strstr(s,"/") == NULL){ //ppdes meter outra condição aqui vá
		char* string = strdup(s);
		char* aux = strsep(&string, "=");
		var = mkVar(aux);
		aux = strsep(&string, ";");
		num = mkInt(atoi(aux));
		instruc = mkInstr(ATRIB, var, num, empty(),0,indice);
		return instruc;
	}
	//ARITMÈTRICAS
	//ADD
	else if(strstr(s,"+") != NULL){
		int tipo = instrucType(s, "+");
		//printf("%d %d\n", tipo, indice);
		char *save, *string, *var;
		switch(tipo){
			case 1:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "+");
				elem2 = mkVar(var);
				var = strsep(&save, "+");
				elem3 = mkVar(var);
				instruc = mkInstr(ADD,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 2:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "+");
				elem2 = mkInt(atoi(var));
				var = strsep(&save, "+");
				elem3 = mkInt(atoi(var));
				instruc = mkInstr(ADD,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 3:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "+");
				elem2 = mkVar(var);
				var = strsep(&save, "+");
				elem3 = mkInt(atoi(var));
				instruc = mkInstr(ADD,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 4:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "+");
				elem2 = mkInt(atoi(var));
				var = strsep(&save, "+");
				elem3 = mkVar(var);
				instruc = mkInstr(ADD,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;			
		}
		return instruc;
	}
	//SUB
	if(strstr(s,"-") != NULL){
		int tipo = instrucType(s, "-");
		char *save, *string, *var;
		switch(tipo){
			case 1:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "-");
				elem2 = mkVar(var);
				var = strsep(&save, "-");
				elem3 = mkVar(var);
				instruc = mkInstr(SUB,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 2:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "-");
				elem2 = mkInt(atoi(var));
				var = strsep(&save, "-");
				elem3 = mkInt(atoi(var));
				instruc = mkInstr(SUB,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 3:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "-");
				elem2 = mkVar(var);
				var = strsep(&save, "-");
				elem3 = mkInt(atoi(var));
				instruc = mkInstr(SUB,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 4:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "-");
				elem2 = mkInt(atoi(var));
				var = strsep(&save, "-");
				elem3 = mkVar(var);
				instruc = mkInstr(SUB,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;			
		}
		return instruc;
	}
	//MUL
	if(strstr(s,"*") != NULL){
		int tipo = instrucType(s, "*");
		char *save, *string, *var;
		switch(tipo){
			case 1:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "*");
				elem2 = mkVar(var);
				var = strsep(&save, "*");
				elem3 = mkVar(var);
				instruc = mkInstr(MUL,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 2:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "*");
				elem2 = mkInt(atoi(var));
				var = strsep(&save, "*");
				elem3 = mkInt(atoi(var));
				instruc = mkInstr(MUL,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 3:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "*");
				elem2 = mkVar(var);
				var = strsep(&save, "*");
				elem3 = mkInt(atoi(var));
				instruc = mkInstr(MUL,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 4:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "*");
				elem2 = mkInt(atoi(var));
				var = strsep(&save, "*");
				elem3 = mkVar(var);
				instruc = mkInstr(MUL,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;			
		}
		return instruc;
	}
	
	//DIV
	if(strstr(s,"/") != NULL){
		int tipo = instrucType(s, "/");
		char *save, *string, *var;
		switch(tipo){
			case 1:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "/");
				elem2 = mkVar(var);
				var = strsep(&save, "/");
				elem3 = mkVar(var);
				instruc = mkInstr(DIV,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 2:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "/");
				elem2 = mkInt(atoi(var));
				var = strsep(&save, "/");
				elem3 = mkInt(atoi(var));
				instruc = mkInstr(DIV,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 3:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "/");
				elem2 = mkVar(var);
				var = strsep(&save, "/");
				elem3 = mkInt(atoi(var));
				instruc = mkInstr(DIV,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;
			case 4:
				string = strdup(s);
				save = strsep(&string, "=");
				elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "/");
				elem2 = mkInt(atoi(var));
				var = strsep(&save, "/");
				elem3 = mkVar(var);
				instruc = mkInstr(DIV,elem1,elem2,elem3,tipo,indice);
				return instruc;
				break;			
		}
		return instruc;
	}
	
	return instruc;

}

void escrever(Instr inst) {
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
    break;
    case DIV:
    if (inst.second.kind == INT_CONST && inst.third.kind == INT_CONST) {
      printf("%s = %d / %d\n", getName(inst.first), getValue(inst.second), getValue(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == STRING) {
      printf("%s = %s / %s\n", getName(inst.first), getName(inst.second), getName(inst.third));
      break;
    }
    if (inst.second.kind == STRING && inst.third.kind == INT_CONST) {
      printf("%s = %s / %d\n", getName(inst.first), getName(inst.second), getValue(inst.third));
      break;
    }
    if (inst.second.kind == INT_CONST && inst.third.kind == STRING) {
      printf("%s = %d / %s\n", getName(inst.first), getValue(inst.second), getName(inst.third));
      break;
    }
    break;
    case READ:
    printf("Ler(%s)\n", getName(inst.first));
    break;
    case PRINT:
    printf("Escrever(%s)\n",getName(inst.first));
    break;
    case START:
    break;
    case QUIT:
    printf("Quit\n");
    break;
    case GOTO:
    printf("Goto %s\n", getName(inst.first));
    break;
    case IF:
    printf("If %s goto L1\n", getName(inst.first));
    break;
    case LABEL:
    printf("Label %s\n", getName(inst.first));    
    break;
    default: 
		printf("Erro!!\n");
  }
}

int run(PROG_LIST lista){
	char*label;
	PROG_CELL cell;
	int value, part1, part2;
	PROG_CELL C1; 
	PROG_CELL C2;
	Instr aux;
	int index;
	while(lista != NULL){
		Instr inst = head(lista);
		//printf("%d", inst.tipo);
		switch(inst.op){
			case START:
				break;
			case QUIT:
				return 0;
				printf("\nFIM\n");
				lista->next = NULL;
				break;
			case PRINT:
				value = getValofCell(lookup(getName(inst.first)));
				printf("%d\n", value);
				break;		
			case READ:
				printf("Valor de %s = ", getName(inst.first));
				scanf("%d", &value);
				insert(getName(inst.first),value);
				//printf("ok");
				break;
			case IF:
				C1 = lookup(getName(inst.first));
				//printf("waaaa");
				value = getValofCell(C1);
				if(value != 0){
					//printf("what");
					label = getName(inst.second);
					int index1 = inst.indice;
					int index2 = getIndex(label,lista);
					lista = lista -> next;
					aux = head(lista);
					while(index2 != aux.indice){
						lista = lista -> next;
						aux = head(lista);
					}					
				}
				break;
			case GOTO: //not done
				label = getName(inst.first);
				index = getIndex(label,lista);
				lista = lista->next;
				aux = head(lista);
				while(index != aux.indice){
					lista = lista -> next;
					aux = head(lista);
				}
				break;
			case LABEL: //do more
				break;
			case ATRIB:
				if (inst.second.kind == INT_CONST) {
					insert(getName(inst.first),getValue(inst.second));
				} else if (inst.second.kind == STRING) {
					insert(getName(inst.second),lookup(inst.first.content.name)->elem); 
				}
					break;
			case ADD:
				switch (inst.tipo) {
					case 1:
						part1 = getValofCell(lookup(getName(inst.second)));
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part1 + part2));
						break;
				    case 2:
						insert(getName(inst.first), (getValue(inst.second) + getValue(inst.third)));
						break;
					case 3:
						part1 = getValofCell(lookup(getName(inst.second)));
						insert(getName(inst.first), (part1 + getValue(inst.third)));
						break;
					case 4:
						//printf("suuuum");
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part2 + getValue(inst.second)));
						break;
				}
				break;
			case SUB:
				switch (inst.tipo) {
					case 1:
						part1 = getValofCell(lookup(getName(inst.second)));
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part1 - part2));
						break;
					case 2:
						insert(getName(inst.first), (getValue(inst.second) - getValue(inst.third)));
						break;
					case 3:
						part1 = getValofCell(lookup(getName(inst.second)));
						insert(getName(inst.first), (part1 - getValue(inst.third)));
						break;
					case 4:
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part2 - getValue(inst.second)));
						break;
				}
				break;
			case MUL:
				switch (inst.tipo) {
					case 1:
						part1 = getValofCell(lookup(getName(inst.second)));
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part1 * part2));
						break;
					case 2:
						insert(getName(inst.first), (getValue(inst.second) * getValue(inst.third)));
						break;
					case 3:
						part1 = getValofCell(lookup(getName(inst.second)));
						insert(getName(inst.first), (part1 * getValue(inst.third)));
						break;
					case 4:
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part2 * getValue(inst.second)));
						break;
				}
				break;
			case DIV:
				switch (inst.tipo) {
					case 1:
					//printf("oooooo");
						part1 = getValofCell(lookup(getName(inst.second)));
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part1 / part2));
						break;
					case 2:
					//printf("oooooo");
						insert(getName(inst.first), (getValue(inst.second) / getValue(inst.third)));
						break;
					case 3:
					//printf("oooooo");
						part1 = getValofCell(lookup(getName(inst.second)));
						//printf("oooooo");
						insert(getName(inst.first), (part1 / getValue(inst.third)));
						break;
					case 4:
					//printf("oooooo");
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part2 / getValue(inst.second)));
						break;
				}
				break;
			default: 
				printf("Erro!!\n");
				break;
		}
		//printf("yee");
		lista = lista -> next;
	}
}
