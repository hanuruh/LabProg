#include "trabalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE * fp;
    
	init_table();
    char* line = NULL;
    size_t line_length = 32;
    ssize_t read;
    
    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE); // see more

    PROG_LIST lista = mkList(mkInstr(START,empty(),empty(),empty()),NULL); // x
    while (( read = getline(&line, &line_length, fp)) != -1){
		//printf("Linha = %s\n", linha);
		removeSpaces(linha);
		//printf("%s\n", linha);
		Instr instruc = convertToInstruc(linha);
		PROG_LIST newInstruc = mkList(instruc,NULL);
		lista = append(lista, newInstruc);
	}
	
	fclose(fp);
	printf("Lista:\n");
	printList(lista);
	printf(".......................PRONTO A COMEÇAR........................\n");
	run(lista);
	
	return 0;
}

