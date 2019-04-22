#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "run.h"

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
				printf("Valor de %s = %d\n", getName(inst.first), value);
				break;		
			case READ:
				printf("Valor de %s ? ", getName(inst.first));
				scanf("%d", &value);
				insert(getName(inst.first),value);
				break;
			case IF:
				C1 = lookup(getName(inst.first));
				value = getValofCell(C1);
				if(value != 0){
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
			case GOTO:
				label = getName(inst.first);
				index = getIndex(label,lista);
				lista = lista->next;
				aux = head(lista);
				while(index != aux.indice){
					lista = lista -> next;
					aux = head(lista);
				}
				break;
			case LABEL:
				break;
			case ATRIB:
				if (inst.second.kind == INT_CONST) {
					insert(getName(inst.first),getValue(inst.second));
				} else if (inst.second.kind == STRING) {
					insert(getName(inst.first), lookup(inst.second.content.name)->elem); 
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
						part1 = getValofCell(lookup(getName(inst.second)));
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part1 / part2));
						break;
					case 2:
						insert(getName(inst.first), (getValue(inst.second) / getValue(inst.third)));
						break;
					case 3:
						part1 = getValofCell(lookup(getName(inst.second)));
						insert(getName(inst.first), (part1 / getValue(inst.third)));
						break;
					case 4:
						part2 = getValofCell(lookup(getName(inst.third)));
						insert(getName(inst.first), (part2 / getValue(inst.second)));
						break;
				}
				break;
			default: 
				printf("Erro!!\n");
				break;
		}
		lista = lista -> next;
	}
}
