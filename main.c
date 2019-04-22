#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "hash.h"
#include "instr.h"
#include "run.h"

int main(int argc, char **argv){
	
	PROG_LIST lista = file_to_list(argv[1]);    
	printf("Lista:\n");
	printList(lista);
	printf(".......................PRONTO A COMEÇAR........................\n");
	run(lista);
	
	return 0;
}

