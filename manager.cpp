#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "myProcess.h"
#include "heap.h"

int main() {

    const int NUMERO_DE_PROCESSOS = 25; //Valor modificável, 
    srand(time(nullptr));

    Queue initial_queue = create_random_queue(NUMERO_DE_PROCESSOS);
    //initial_queue.print();
    
    MinHeap heap;
    heap.build_from_queue(initial_queue);

    std::cout << "\n--------------------------------------------------\n";
    std::cout << ">>> INICIANDO GERENCIADOR DE PROCESSOS <<<\n";
    std::cout << "Número inicial de processos: " << heap.size() << std::endl;
    
    int cycle_count = 1;

    while (!heap.is_empty()) {

        std::cout << "\n--------------------------------------------------\n";
        std::cout << "\n>>> CICLO N°" << cycle_count << " <<<\n";
        std::cout << "Processos no heap: " << heap.size() << std::endl;

        int n = (rand() % heap.size()) + 1;
        std::cout << "Serão executados " << n << " processos." << std::endl << std::endl;
        std::cout << "\nIniciando execução dos processos..." << std::endl;

        std::vector<Process> modified_processes; //vetor auxiliar

        for (int i = 0; i < n; ++i) {

            Process* p_ptr = heap.get_process_at(i);
            if (p_ptr) {
                //calculo pre execução
                int old_key = p_ptr->time_to_kill - p_ptr->time_used;

                p_ptr->execute_process();

                //calculo pos execução
                int new_key = p_ptr->time_to_kill - p_ptr->time_used;

                std::cout << "-> Processo de ID " << p_ptr->id << " foi executado." << std::endl;
                std::cout << "Valor da key anterior: " << old_key << std::endl;
                std::cout << "Valor da nova key: " << new_key << "." << std::endl;
                
                modified_processes.push_back(*p_ptr);
            }
        }

        

        std::cout << "\nAtualizando os processos e rebalanceando o heap..." << std::endl;
        for (const auto& p : modified_processes) {
            heap.update_key(p.id, p.time_used);
        }
        std::cout << "Rebalanceamento finalizado!" << std::endl;
        std::cout << std::endl << std::endl;
        

        std::cout << "Iniciando remoção de processos finalizados..." << std::endl;
        int removed_count = 0;
        while (!heap.is_empty() && heap.get_root_key() <= 0) {
            Process removed_process = heap.remove_min();
            std::cout << "  -> Processo de ID " << removed_process.id << " REMOVIDO (Key=0).\n";
            removed_count++;
        }
        if (removed_count == 0) {
            std::cout << "  -> Raiz nao removida (Key != 0).\n";
        }
        
        cycle_count++;
        std::cout << "\n>>> CICLO FINALIZADO <<<" << std::endl;
    }

    std::cout << "\n--------------------------------------------------\n";
    std::cout << ">>> SIMULACAO FINALIZADA <<<\n";
    std::cout << "Todos os processos foram concluidos em " << cycle_count - 1 << " ciclos.\n";

    return 0;
}