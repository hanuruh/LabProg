#include "trabalho.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	Elem var1;
	var1= mkVar("x");
	
	Elem var2;
	var2= mkInt(2);
	
	Elem var3;
	var3 = empty();
	
	Instr first_instr;
	first_instr = mkInstr(ATRIB,var1,var2,var3); //x = 2
	
	PROG_LIST p_list = newList(first_instr,newlist(mkInstr(ADD,mkvar("y"),mkvar("x"),mkInt(4)))); // lista tipo [x = 2, y = x + 4]
	
	return 0;
}

