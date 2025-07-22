#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

//troca os dois nodes, função auxiliar utilizada por heapify_up e heapify_down
static void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

//troca dois nodes a depender dos valores de suas keys
static void heapify_down(MinHeap *h, int index) {

    int menor = index;
    int filho_esquerdo = 2 * index + 1;
    int filho_direito = 2 * index + 2;

    // Verifica se o filho esquerdo existe e é menor que o nó atual
    if (filho_esquerdo < h->size && h->nodes[filho_esquerdo].key < h->nodes[menor].key) {
        menor = filho_esquerdo;
    }

    // Verifica se o filho direito existe e é menor que o menor encontrado até agora
    if (filho_direito < h->size && h->nodes[filho_direito].key < h->nodes[menor].key) {
        menor = filho_direito;
    }

    // Se o menor não for o próprio nó, troca e continua o processo recursivamente
    if (menor != index) {
        swap(&h->nodes[index], &h->nodes[menor]);
        heapify_down(h, menor);
    }
}


//troca dois nodes a depender dos valores das keys
static void heapify_up(MinHeap *h, int index) {

    int pai = (index - 1) / 2;

    // Enquanto o nó não for a raiz e for menor que seu pai, troca
    if (index > 0 && h->nodes[index].key < h->nodes[pai].key) {
        swap(&h->nodes[index], &h->nodes[pai]);
        // Continua o processo para a nova posição do nó
        heapify_up(h, pai);
    }
}


static MinHeap* create_heap(int capacity) {
    MinHeap *h = (MinHeap*) malloc(sizeof(MinHeap));
    if (!h) {
        perror("Erro ao alocar memória para o heap");
        exit(EXIT_FAILURE);
    }
    h->nodes = (HeapNode*) malloc(capacity * sizeof(HeapNode));
    if (!h->nodes) {
        perror("Erro ao alocar memória para os nós do heap");
        free(h);
        exit(EXIT_FAILURE);
    }
    h->size = 0;
    h->capacity = capacity;
    return h;
}