#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

void MinHeap::build_from_queue(const Queue& q) {

    if (q.is_empty()) {
        return;
    }

    this->nodes.reserve(q.size());

    Queue::Node* current = q.start;
    while (current != nullptr) {
        HeapNode newNode;
        newNode.process = current->process;
        newNode.key = current->process.time_to_kill - current->process.time_used;
        this->nodes.push_back(newNode);
        current = current->next;
    }

    this->build_heap();
}

MinHeap::MinHeap() {}

bool MinHeap::is_empty() const {
    return this->nodes.empty();
}

void MinHeap::build_heap() {
    for (int i = (this->nodes.size() / 2) - 1; i >= 0; i--) {
        this->heapify_down(i);
    }
}


void MinHeap::heapify_down(int index) {
    int menor = index;
    int filho_esquerdo = 2 * index + 1;
    int filho_direito = 2 * index + 2;
    int size = this->nodes.size();

    if (filho_esquerdo < size && this->nodes[filho_esquerdo].key < this->nodes[menor].key) {
        menor = filho_esquerdo;
    }
    if (filho_direito < size && this->nodes[filho_direito].key < this->nodes[menor].key) {
        menor = filho_direito;
    }

    if (menor != index) {
        std::swap(this->nodes[index], this->nodes[menor]);
        this->heapify_down(menor);
    }
}

void MinHeap::heapify_up(int index) {
    if (index == 0) return;
    int pai = (index - 1) / 2;

    if (this->nodes[index].key < this->nodes[pai].key) {
        std::swap(this->nodes[index], this->nodes[pai]);
        this->heapify_up(pai);
    }
}

void MinHeap::insert(const Process& p) {
    HeapNode newNode;
    newNode.process = p;
    newNode.key = p.time_to_kill - p.time_used;
    
    this->nodes.push_back(newNode);
    this->heapify_up(this->nodes.size() - 1);
}


Process MinHeap::remove_min() {
    if (this->is_empty()) {
        throw std::runtime_error("Tentativa de remover de um heap vazio.");
    }
    Process min_process = this->nodes.front().process;
    this->nodes[0] = this->nodes.back();
    this->nodes.pop_back();

    if (!this->is_empty()) {
        this->heapify_down(0);
    }
    return min_process;
}

void MinHeap::update_key(unsigned int process_id, int new_time_used) {
    int index = -1;
    for (size_t i = 0; i < this->nodes.size(); ++i) {
        if (this->nodes[i].process.id == process_id) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        int old_key = this->nodes[index].key;
        this->nodes[index].process.time_used = new_time_used;
        this->nodes[index].key = this->nodes[index].process.time_to_kill - new_time_used;

        if (this->nodes[index].key < old_key) {
            this->heapify_up(index);
        } else {
            this->heapify_down(index);
        }
    }
}

Queue MinHeap::heap_to_queue() {
    
    MinHeap temp_heap = *this;

    // Cria um objeto Queue usando seu construtor padrão.
    Queue q;

    // Usa os métodos da classe Queue para popular a nova fila.
    while (!temp_heap.is_empty()) {
        q.insert(temp_heap.remove_min());
    }
    return q; // Retorna o objeto Queue por valor.
}

Process* MinHeap::get_process_at(int index) {
    if (index >= 0 && index < this->nodes.size()) {
        return &this->nodes[index].process;
    }
    return nullptr;
}

int MinHeap::get_root_key() const {
    if (is_empty()) {return -1;}
    return this->nodes.front().key;
}

int MinHeap::size() const {
    return this->nodes.size();
}