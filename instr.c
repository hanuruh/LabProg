#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "instr.h"


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
		ch = mkVar(aux);
		aux = strsep(&string, "o");
		aux = strsep(&string, "o");
		aux = strsep(&string, ";");
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
	//ATRIB 
	else if(strstr(s,"+") == NULL && strstr(s,"-") == NULL && strstr(s,"*") == NULL && strstr(s,"/") == NULL){ //ppdes meter outra condição aqui vá
		char* string = strdup(s);
		char* aux = strsep(&string, "=");
		var = mkVar(aux);
		aux = strsep(&string, ";");
		num = mkInt(atoi(aux));
		if(atoi(aux) == 0){ //x = string
			instruc = mkInstr(ATRIB, var, mkVar(aux), empty(),0,indice);
		}
		else		 // x = number
			instruc = mkInstr(ATRIB, var, num, empty(),0,indice);
		return instruc;
	}
	//ARITMÈTRICAS
	//ADD
	else if(strstr(s,"+") != NULL){
		int tipo = instrucType(s, "+");
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
