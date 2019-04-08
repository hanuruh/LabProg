#include "trabalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv){
    init_table();
    FILE * fp;
    char line[1024];
    char c;
    size_t line_length = 1024;
    ssize_t read;
    int indexx = 1, i=0;
    
    fp = fopen(argv[1], "r");
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
	printf("Lista:\n");
	printList(lista);
	printf(".......................PRONTO A COMEÇAR........................\n");
	run(lista);
	
	return 0;
}

