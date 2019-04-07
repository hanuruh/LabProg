#define HASH_SIZE 20
#define MULTIPLIER 32

/*******************PROG_FUNC**********************/
typedef enum {ATRIB, ADD, SUB, MUL, DIV, IF_I, PRINT, READ, GOTO_I, LABEL} OpKind;

typedef enum {EMPTY, INT_CONST, STRING} ElemKind;


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

Elem mkVar(char *s);
Elem mkInt(int n);
Elem empty();
Instr mkInstr(OpKind op, Elem x, Elem y, Elem z); //exemplo k = (mkInstr(ADD,mkVar("x"),mkVar("y"),mkInt(2)); y = x + 2 . k vai representar e memoria a instrução
Instr convertToInstruc(char*);
int getValue(Elem x);
int instrucType(char* str, char* ch); 
char* getString(Elem x);
void escrever(Instr intruc);
void removeSpaces(char *str);
/*******************PROG_FUNC**********************/

/*******************LIST**********************/
typedef struct list{ // fazer apontador a apontar para o ultimo elemento da lista ?
	Instr elem;
	struct list *next;
}PROG_LIST;

PROG_LIST mkList(Instr head, PROG_LIST tail);
PROG_LIST tail(PROG_LIST l);
PROG_LIST map(int (*f)(int), PROG_LIST l); 
PROG_LIST filter(Bool (*p)(int), PROG_LIST l); //bool ou int ?
PROG_LIST addLast(Instr n, PROG_LIST l1);
PROG_LIST append(PROG_LIST l1, PROG_LIST l2);
PROG_LIST readList();
int head(PROG_LIST l);
int length(PROG_LIST l);
int elem_n(int n, PROG_LIST l);
void printList(PROG_LIST l);
void run(PROG_LIST l);
/*******************LIST**********************/

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
char* getNameofCell(PROG_CELL p);
/*******************HASHTABLE**********************/



