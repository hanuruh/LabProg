#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "hash.h"

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

PROG_LIST last(PROG_LIST l) {

  while(l->next!=NULL) {
    l= l->next;
  }

  return l;

}

PROG_LIST file_to_list(char file_name[]){
	FILE *fp;
	init_table();
    char line[1024];
    char c;
    size_t line_length = 1024;
    ssize_t read;
    int indexx = 1, i=0;
	
	fp = fopen(file_name, "r");
    if (fp == NULL){
        printf("ERRO ABRIR FICHEIRO\n");        
		return 0;
	} 
	
    PROG_LIST lista = newList(mkInstr(START,empty(),empty(),empty(),0,0),NULL);
    while ((fgets(line, sizeof(line), fp))!=NULL){
			//printf("Linha = %s\n", line);
			removeSpaces(line);
			//printf("%s\n", line);
			Instr instruc = convertToInstruc(line,indexx);
			indexx++;
			lista = addLast(instruc, lista);
			
	}	
	fclose(fp);
	
	return lista;

}
