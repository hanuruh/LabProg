#define HASH_SIZE 20

typedef struct{
     ElemKind kind;
		union{ 
           int val;
           char *name;
        } content;
}Elem;

typedef struct{
     OpKind op;
     Elem first, second, third;
} Instr;

typedef enum {ATRIB, ADD, SUB, MUL, IF_I, PRINT, READ, GOTO_I, LABEL,...} OpKind;

typedef enum {EMPTY, INT_CONST, STRING} ElemKind;

typedef struct list{ // fazer apontador a apontar para o ultimo elemento da lista
	Instr elem;
	struct list *next;
}PROG_LIST;

Elem mkVar(char *s);
Elem mkInt(int n);
Elem empty();
Instr mkInstr(Opkind op, Elem x, Elem y, Elem z); //exemplo k = (mkInstr(ADD,mkVar("x"),mkVar("y"),mkInt(2)); y = x + 2 . k vai representar e memoria a instrução
PROG_LIST mkList(Instr head, PROG_LIST tail);

int getValue(Elem x);
char* getString(Elem x);
void escrever(Instr intruc);

/*******************HASHTABLE**********************/
typedef struct list{
	char *chave;	
	int elem;
	struct list *next;
}*PROG_CELL;

unsigned int hash(char *s);

PROG_CELL table[HASH_SIZE];

PROG_CELL lookup(char *s);

void insert(char *s, int value);
void init_table();
void PrintCell(PROG_CELL c);
int getValofCell(PROG_CELL p);
/*******************HASHTABLE**********************/

