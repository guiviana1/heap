#ifndef MY_PROCESS_H
#define MY_PROCESS_H

#include <bits/stdc++.h>
#include <string>


typedef enum {
    VI, EX, AWK, SED, CC, MAKE, NROFF, TROFF, TBL, EQN, YACC, LEX,
    ADB, DB, CSH, EMACS, TIP, CRON, FTP, TELNET, PROGRAM_COUNT
} UnixProgram;

class Process {
public:

    unsigned int id;
    UnixProgram name;
    unsigned int time_to_kill;
    unsigned int time_used;

    Process();

    void update_used_time(unsigned int time);
    void execute_process();
    std::string get_name() const;
};

class Queue {
private:

    struct Node {
        Process process;
        Node* next;
    };

    Node* start;
    Node* end;
    int current_size;

public:
    Queue();    
    ~Queue();   
  
    Queue(const Queue& other) = delete; 
    Queue& operator=(const Queue& other) = delete; 
    Queue(Queue&& other) noexcept;

    void insert(const Process& p);
    bool is_empty() const;
    int size() const;
    void print() const; 

    friend class MinHeap; //boa pratica para permitir o acesso do MinHeap aos atributos aqui da classe Queue
};

Queue create_random_queue(int n);

std::string get_program_name(UnixProgram program);

#endif // MY_PROCESS_H