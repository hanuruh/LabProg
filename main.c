#include "trabalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
  /*******TESTAR************
  Elem var1 = mkVar("x");
  Elem var2 = mkInt(1);
  Elem var3 = empty();
  Instr inst1 = mkInstr(ATRIB,var1,var2,var3);
  escreverDEBBUG(inst1);
  Elem var4 = mkVar("y");
  Elem var5 = mkInt(2);
  Instr inst2 = mkInstr(ADD,var4,var1,var5);
  escreverDEBBUG(inst2);
  Elem var6 = mkVar("z");
  Instr inst3 = mkInstr(SUB,var6,var4,var1);
  escreverDEBBUG(inst3);
  Elem var7 = mkVar("w");
  Instr inst4 = mkInstr(MUL,var7,var5,var4);
  escreverDEBBUG(inst4);
  **************************/
  
  /*********MAIN************/
  
  FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("/etc/motd", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
	
	return 0;
}

