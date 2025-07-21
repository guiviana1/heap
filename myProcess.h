#ifndef MY_PROCESS_H
#define MY_PROCESS_H

#include <time.h>
#define IDMAXREF 500

/**
 *
 * Enum para representar programas Unix
 *
 */
typedef enum {
    VI,
    EX,
    AWK,
    SED,
    CC,
    MAKE,
    NROFF,
    TROFF,
    TBL,
    EQN,
    YACC,
    LEX,
    ADB,
    DB,
    CSH,
    EMACS,
    TIP,
    CRON,
    FTP,
    TELNET,
    PROGRAM_COUNT // usado para saber o total de programas
} UnixProgram;

/**
 *
 * Função para obter o nome do programa como string
 *
 */
const char* getProgramName(UnixProgram program);

/**
 *
 * Função que pega um UnixProgram aleatoriamente
 *
 */
UnixProgram getRandomProgram();

/**
 * 
 * Estrutura para representar processos de programas Unix em execução
 *
 */
typedef struct {
    unsigned int id;
    UnixProgram name;
    unsigned int time_to_kill;
    unsigned int time_used;
} Process;

/**
 *
 * Função que irá criar processos de forma pseudo-aleatória
 *
 */
Process create_Process();

/**
 *
 * Função que atualiza o valor do time_used de um process
 */
void update_used_time(Process *p, int time);

/**
 *
 * Função que simula a execução de um processo p
 */
void execute_Process(Process *p);

/**
 *
 * Estrutura para representar os node em uma fila
 *
 */
typedef struct node {
  Process process;
  struct node *next;
} Node;

/**
 *
 * Estrutura para representar a fila
 *
 */
typedef struct {
  int size;
  Node *start;
  Node *end;
} Queue;

/**
 *
 * Inicializa uma fila vazia
 *
 */
 Queue* init_queue();

/**
 *
 * Insere um novo processo na fila
 *
 */
void insert_in_queue(Queue *q, Process p);

/**
 *
 * Insere n processos aleatoriamente no fila
 *
 */
Queue* create_queue_of_process(int n);

/**
 *
 * Imprime toda a fila de processos
 *
 */
void print_queue_of_process(Queue *q);


#endif

