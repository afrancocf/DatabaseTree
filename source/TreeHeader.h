
/*____________ ESTRUTURA DE DADOS ____________*/

#define ORDEM 50
#define REGS_POR_PAGINA 15
#define MAXSTR 20

typedef struct Register
{
	int key,age;
	char name[MAXSTR];
}Register;

typedef struct TerminalNode
{
	Register reg[REGS_POR_PAGINA];
	int next_node;
	int qtdeReg;
}TerminalNode;

typedef struct IndexNode
{
	int pointers[(2*ORDEM)+1]; //Se for n� folha o valor ser� negativo.
	int keys[2*ORDEM]; //index
	int idNode;
	_Bool leaf;
	int qtdeKeys;
}IndexNode;

//Pilha de n�s de �ndices
typedef struct IndexStack
{
	IndexNode indexNode;
	struct IndexStack *next;
}IndexStack;

typedef struct
{
	IndexStack *top;
}StackTop;

//fila para busca em largura nos �ndices
typedef struct IndexQueue
{
	IndexNode indexNode;
	struct IndexQueue *next;
}IndexQueue;

//fila para busca em largura nos �ndices
typedef struct TerminalQueue
{
	TerminalNode terminalNode;
	struct TerminalQueue *next;
}TerminalQueue;

typedef struct
{
	IndexQueue *first,*last;
}IQueue;

typedef struct
{
	TerminalQueue *first,*last;
}TQueue;

/*____________ BIBLIOTECAS USADAS ____________*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*____________ FUN��ES AUXILIARES ____________*/

void getstr(char * str,unsigned sizeStr);
FILE* checkFileIndex(void);
FILE* checkFileTerminal(void);
int numberRegisters(FILE* f,char nodetype);
int buscaBinaria(Register *array,int key);


/*____________ FUN��ES PARA N�S DE �NDICE ____________*/

_Bool pushStack(StackTop *stack,IndexNode *inode);
IndexNode* popStack(StackTop *head);
void initIndexNode(IndexNode *inode);
void shiftPointers(int *pointers,int pos,int pos_val);
int splitIndex(IndexNode *istack,int key, IndexNode *split_inode,int nreg);
void createSplitIndex(StackTop *istack,int nreg,int promotedKey,FILE *fi);
_Bool enQueueIndex(IQueue *queue,IndexNode *inode);
IndexNode* deQueueIndex(IQueue *queue);
int inserirOrdenadoInode(int *index_keys,int key);
void removeOrdenadoInode(IndexNode *inode,int pos);


/*____________ FUN��ES PARA TERMINAIS ____________*/

_Bool enQueueTerminal(TQueue *queue,TerminalNode *tnode);
TerminalNode* deQueueTerminal(TQueue *queue);
void initTerminalNode(TerminalNode *tnode);
TerminalNode splitTerminal(Register *set_keys,Register *reg,int *qtdeReg);
void inserirOrdenadoTnode(Register *set_keys,Register *reg);
int removeOrdenadoTnode(Register *set_keys,int key);


/*____________ DEFINI��ES DE FUN��ES PRINCIPAIS ____________*/

_Bool insereRegistro(FILE *fi,FILE *ft,Register *reg);
Register* consultaRegistro(FILE *fi,FILE *ft,int key);
Register* slowQuery(FILE *ft,int key);
_Bool removeRegistro(FILE *fi,FILE *ft,int key);
void imprimeArvore(FILE *fi,FILE *ft);
void imprimeNosTerminais(FILE *ft);



void getstr(char * str,unsigned sizeStr)
{
	int i = 0,size;
	scanf("%[^\n]%*c", str);
	size = strlen(str);
	if(size > sizeStr)
	{
		//Perigoso, mas o scanf tem um limite, ent�o na pr�xima leitura n�o vem lixo ap�s o \0.
		str[sizeStr] = '\0';
		size = sizeStr;
	}

	for(i=0;i < size;i++)
	{
		str[i] = tolower(str[i]);
	}

}
