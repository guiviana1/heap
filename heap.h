#ifndef HEAP_H
#define HEAP_H

#include <bits/stdc++.h>
#include "myProcess.h"

struct HeapNode {
    int key;
    Process process;
};

class MinHeap {
public:

    //explicit MinHeap(const Queue& q);
    void build_from_queue(const Queue& q);
    MinHeap();

    Process* get_process_at(int index);
    int get_root_key() const;
    int size() const;

    Process remove_min();
    void insert(const Process& p);
    void update_key(unsigned int process_id, int new_time_used);
    bool is_empty() const; // const: este método não modifica o objeto

    Queue heap_to_queue();

private:
    std::vector<HeapNode> nodes;

    void heapify_down(int index);
    void heapify_up(int index);
    void build_heap();
};

#endif
