#ifndef HEAP_H
#define HEAP_H

#include "myProcess.h"

typedef struct {
    HeapNode *nodes;  // Array dinâmico para armazenar os nós do heap
    int size;         // Número atual de elementos no heap
    int capacity;     // Capacidade máxima do array
} MinHeap;
//essa é a estrutura fixa do nosso Heap, que contém um array de HeapNodes.

typedef struct {
    int key;          // A chave de prioridade: time_to_kill - time_used 
    Process process;  // O processo em si, que contem as variaveis time_to_kill e time_used
} HeapNode;
//esse é o node que será utiliado no Heap

// Cria e retorna um heap a partir de uma fila de processos
MinHeap* convert_queue_to_heap(Queue *q);
//essa função tem o tipo MinHeap porque teremos algo do tipo MinHeap heap ; heap = convert_queue_to_heap(queue)

// Converte um heap de volta para uma estrutura de fila
Queue* convert_heap_to_queue(MinHeap *h);
//e aqui teremos algo do tipo Queue fila = convert_heap_to_queue(heap)


// Atualiza a chave de um nó específico no heap (identificado pelo ID do processo)
void update_key(MinHeap *h, unsigned int process_id, int new_time_used);
//essa função recebe um MinHeap, 

void insert_heap(MinHeap *h, Process p);
// Insere um único processo no heap

Process remove_min(MinHeap *h);
// Remove e retorna o processo com a menor chave (a raiz)

int is_empty(MinHeap *h);
// Verifica se o heap está vazio

void free_heap(MinHeap *h);
// Libera a memória alocada para o heap


#endif
