#include <stdio.h>
#include <stdlib.h>
#include "myProcess.h"
#include "heap.h"

int main(int argc, char *argv[]) {
  int n_process;
  if (argc != 2) {
    fprintf(stderr, "%s simula o gereciamento de 0 processos\n", argv[0]);
    return 1;
  }
  n_process = atoi(argv[1]);
  if (n_process <= 0) {
    fprintf(stderr, "A quantidade de processo deve ser maior que 0.\n");
    return 1;
  }
  Queue *q = create_queue_of_process(n_process);
  /**
  while(teste para manter o loop até o heap ficar vazio){
    este loop é onde deve ficar a lógica descrito no pdf em anexo
  }
  */
  return 0;
}
