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

PROG_LIST tail(PROG_LIST l){
	return(l->next);
}

PROG_LIST map(int (*f)(int),PROG_LIST l){
	if(l==NULL) return NULL;
	else{
		int x = head(l);
		PROG_LIST r = tail(l);
		return newList(f(x),map(f,r));
	}
}

PROG_LIST filter(Bool (*p)(int), PROG_LIST l){
	if(l==NULL) return NULL;
	else{
		if(p(head(l)) == TRUE)
			return newList(head(l), filter(p,tail(l)));
		else
			return filter(p,tail(l));
	}
}

PROG_LIST readList(){
	int n;
	char c;
	scanf("%d%c", &n, &c);
	PROG_LIST new = newList(n,NULL);
	while( c == ' '){
		scanf("%d%c", &n, &c);	
		addLast(n,new);	
	}
	return new;	
}

int head(PROG_LIST l){
	if(l != NULL)
		return(l -> elem);
}

int length(PROG_LIST l){
	if(l==NULL) return 0;
	else return(1 + length(tail(l)));
}

int elem_n(int n, PROG_LIST l){
	int count=0;
	while(count<n){
		l=l->next;
		count++;
	}
	return(l->elem);
}

void printList(PROG_LIST l){
	printf("[ ");
	while(l != NULL){
	printf("%d ", l -> elem);
	l = tail(l);	
	}
	printf("]\n");

}

void run(PROG_LIST l){
	char* label;
	PROG_LIST lista;
	int value;
	//células que contêm valores de x e respetivo value (se existir)
	//C1 = lookup(x) C1 vai ter a célula de x
	//C1->elem delvolve valor de x (se existir)
	PROG_CELL C1; 
	PROG_CELL C2;
	while(lista != NULL){
		Instr inst = head(lista);
		switch(inst.op){
			case START:
				break;
			case QUIT:
				return 0;
				break;
			case PRINT:
				printInstruc(inst);
				break;		
			case READ:
				printf("Valor de %s = ", getName(inst.first));
				scanf("%d\n", &val);
				insert(getName(inst.first),val);
				break;
			case GOTO: //not done
				label = getName(instfirst);
				break;
			case ATRIB:
				if (inst.second.kind == INT_CONST) {
					insert(getName(inst.first),getValue(inst.second));
				} else if (inst.second.kind == STRING) {
					insert(inst.first,inst.second); 
				}
					break;
			case ADD: //switch tipo!!
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
		lista = lista -> tail;
	}
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

void removeSpaces(char* str){
	str[strln(str)-2] = '\0';
	int count = 0, i;
	for(i=0, str[i]; i++)
		if(str[i] != ' ')
			str[count++] = str[i];
	str[count] = '\0';	
}

//Saber o tipo de instruções
//Muito util para operações aritmétricas 
//Tipo 1 = str str
//Tipo 2 = int int
//Tipo 3 = str int
//Tipo 4 = int str
int instrucType(char* str, char* ch){
	char *save, *string, *var1, *var2, *type1, *type2;
	int temp1, temp2, type;
	
	string = strdup(str);
	if(string == NULL)
		return -1;
	
	save = strsep(&string, "=");
	save = strsep(&string, "=");
	type1 = strdup(save);
	type2 = strup(save);
	
	var1 = strsep(&type1, ch);
	if((var1[0] >= 0x60 && var1[0] <= 0x7B)){ //detetar str
		var1 = strsep(&type1, ch);
		if((var1[0] >= 0x61 && var1[0] <= 0x7A)){ //str str
			tipo = 1;
			return tipo;
		}else{ //str int
			temp2 = atoi(var1);
			tipo = 3;
			return tipo;
		}
	}
	
	var2 = strsep(&type2, ch);
	if(!(var2[0] >= 0x60 && var2[0] <= 0x7B)){ //detetar int
		temp1 = atoi(var2);
		var2 = strsep(&type2, ch);
		if(!(var2[0] >= 0x61 && var2[0] <= 0x7A)){ //int int
			temp2 = atoi(var2);
			tipo = 2;
			return tipo;
		}else{ //int str
			tipo = 4;
			return tipo;
		}
	}
}

Instr convertToInstruc(char* s){
	Instr instruc;
	//QUIT
	if(strstr(s,"quit") != NULL){
		instruc = mkInstr(QUIT,empty(),empty(),empty(),0);
		return instruc;
	}
	//READ ler(x)
	if(strstr(s,"ler") != NULL){
		char* string = strdup(s);
		char* aux = strsep(&string, "("); //usar outra coisa em vez disto, tipo dropar o resto da string
		aux = strsep(&string, ")");
		Elem ch = mkVar(aux);
		instruc = mkInstr(READ,ch,empty(),empty(),0);
		return instruc;
	}
	//PRINT escrever(x)
	if(strstr(s,"escrever") != NULL){
		char* string = strdup(s);
		char* aux = strsep(&string, "(");
		aux = strsep(&string, ")");
		Elem ch = mkVar(aux);
		instruc = mkInstr(PRINT,ch, empty(),empty(),0);
		return instruc;
	}
	//GOTO 
	if(strstr(s,"goto") != NULL){
		char* string = strdup(s);
		char* aux = strsep(&string, ":");
		aux = strsep(&string, ":");
		Elem ch = mkVar(aux);
		instruc = mkInstr(GOTO,ch,empty(),empty(),0);
		return instruc;
	}
	//LABEL
	if(strstr(s,"label") != NULL) {
		char* string = strdup(s);
		char* aux = strsep(&string, ":");
		aux = strsep(&string, ":");
		Elem ch = mkVar(aux);
		instruc = mkInstr(LABEL,ch,empty(),empty(),0);
		return instruc;
	}
	//ATRIB x = 2
	if(strstr(s,"+") == NULL && strstr(s,"-") == NULL && strstr(s,"*") == NULL && strstr(s,"/") == NULL){ //ppdes meter outra condição aqui vá
		char* string = strdup(s);
		char* aux = strsep(&string, "=");
		Elem var = mkVar(aux);
		aux = strsep(&string, ";");
		Elem num = mkInt(atoi(aux));
		instruc = mkInstr(ATRIB, var, num, empty(),0);
		return instruc;
	}
	//ARITMÈTRICAS
	//ADD
	if(strstr(s,"+") != NULL){
		int tipo = instrucType(s, "+");
		char *save, *string, *var;
		switch(tipo){
			case 1:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "+");
				Elem elem2 = mkVar(var);
				var = strsep(&save, "+");
				Elem elem3 = mkVar(var);
				instruc = mkInstr(ADD,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 2:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "+");
				Elem elem2 = mkInt(atoi(var));
				var = strsep(&save, "+");
				Elem elem3 = mkInt(atoi(var));
				instruc = mkInstr(ADD,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 3:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "+");
				Elem elem2 = mkVar(var);
				var = strsep(&save, "+");
				Elem elem3 = mkInt(atoi(var));
				instruc = mkInstr(ADD,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 4:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "+");
				Elem elem3 = mkInt(atoi(var));
				var = strsep(&save, "+");
				Elem elem2 = mkVar(var);
				instruc = mkInstr(ADD,elem1,elem2,elem3,tipo);
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
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "-");
				Elem elem2 = mkVar(var);
				var = strsep(&save, "-");
				Elem elem3 = mkVar(var);
				instruc = mkInstr(SUB,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 2:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "-");
				Elem elem2 = mkInt(atoi(var));
				var = strsep(&save, "-");
				Elem elem3 = mkInt(atoi(var));
				instruc = mkInstr(SUB,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 3:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "-");
				Elem elem2 = mkVar(var);
				var = strsep(&save, "-");
				Elem elem3 = mkInt(atoi(var));
				instruc = mkInstr(SUB,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 4:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "-");
				Elem elem3 = mkInt(atoi(var));
				var = strsep(&save, "-");
				Elem elem2 = mkVar(var);
				instruc = mkInstr(SUB,elem1,elem2,elem3,tipo);
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
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "*");
				Elem elem2 = mkVar(var);
				var = strsep(&save, "*");
				Elem elem3 = mkVar(var);
				instruc = mkInstr(MUL,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 2:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "*");
				Elem elem2 = mkInt(atoi(var));
				var = strsep(&save, "*");
				Elem elem3 = mkInt(atoi(var));
				instruc = mkInstr(MUL,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 3:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "*");
				Elem elem2 = mkVar(var);
				var = strsep(&save, "*");
				Elem elem3 = mkInt(atoi(var));
				instruc = mkInstr(MUL,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 4:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "*");
				Elem elem3 = mkInt(atoi(var));
				var = strsep(&save, "*");
				Elem elem2 = mkVar(var);
				instruc = mkInstr(MUL,elem1,elem2,elem3,tipo);
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
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "/");
				Elem elem2 = mkVar(var);
				var = strsep(&save, "/");
				Elem elem3 = mkVar(var);
				instruc = mkInstr(DIV,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 2:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "/");
				Elem elem2 = mkInt(atoi(var));
				var = strsep(&save, "/");
				Elem elem3 = mkInt(atoi(var));
				instruc = mkInstr(DIV,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 3:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "/");
				Elem elem2 = mkVar(var);
				var = strsep(&save, "/");
				Elem elem3 = mkInt(atoi(var));
				instruc = mkInstr(DIV,elem1,elem2,elem3,tipo);
				return instruc;
				break;
			case 4:
				string = strdup(s);
				save = strsep(&string, "=");
				Elem elem1 = mkVar(save);
				save = strsep(&string, "=");
				var = strsep(&save, "/");
				Elem elem3 = mkInt(atoi(var));
				var = strsep(&save, "/");
				Elem elem2 = mkVar(var);
				instruc = mkInstr(DIV,elem1,elem2,elem3,tipo);
				return instruc;
				break;			
		}
		return instruc;
	}
	
	return instruc;

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
    case LABEL:
    printf("Label %s\n", getName(inst.first));    
    break;
    default: 
		printf("Erro!!\n");
  }
}
