#include "myProcess.h"
#include <iostream>
#include <vector>
#include <random>   
#include <ctime>    

static std::mt19937 generator(time(nullptr));
int random_int(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
} //função que calcula o randomnumber para 

std::string get_program_name(UnixProgram program) {
  
    static const std::vector<std::string> names = {
        "vi", "ex", "awk", "sed", "cc", "make", "nroff", "troff", "tbl",
        "eqn", "yacc", "lex", "adb", "db", "csh", "emacs", "tip",
        "cron", "ftp", "telnet"
    };

    if (program >= 0 && program < PROGRAM_COUNT) {
        return names[program];
    }
    return "unknown";
}

Queue create_random_queue(int n) {
    Queue q;
    for (int i = 0; i < n; ++i) {
        q.insert(Process());
    }
    return q;
}



Process::Process() {
    this->id = random_int(1, 500);
    this->name = static_cast<UnixProgram>(random_int(0, PROGRAM_COUNT - 1));
    this->time_to_kill = random_int(1, 999);
    this->time_used = 0;
}

void Process::update_used_time(unsigned int time) {
    this->time_used = time;
}

void Process::execute_process() {
    // Simula um tempo de execução que não excede o tempo para matar.
    if (this->time_to_kill > this->time_used) {
        unsigned int time_in_cpu = random_int(1, this->time_to_kill - this->time_used);
        this->time_used += time_in_cpu;
    }
}

std::string Process::get_name() const {
    return get_program_name(this->name);
}


//funções da Queue ---------------------------------------------------
Queue::Queue() : start(nullptr), end(nullptr), current_size(0) {}

Queue::~Queue() {
    Node* current = start;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void Queue::insert(const Process& p) {
    Node* newNode = new Node{p, nullptr}; // Usa 'new' em vez de 'malloc'
    if (is_empty()) {
        start = newNode;
        end = newNode;
    } else {
        end->next = newNode;
        end = newNode;
    }
    current_size++;
}

bool Queue::is_empty() const {
    return current_size == 0;
}

int Queue::size() const {
    return current_size;
}

void Queue::print() const {
    Node* current = start;
    while (current != nullptr) {
        // Usa std::cout para impressão
        std::cout << "Process id=" << current->process.id
                  << ", Program=" << current->process.get_name()
                  << ", time_to_kill=" << current->process.time_to_kill
                  << ", time_used=" << current->process.time_used << std::endl;
        current = current->next;
    }
}