#include "lib.h"
#include "utils.h"
#include <stdio.h>


int main(int argc, char* argv[]){
  control_argc(argc);

  char** dictionary = read_dictionary(argv[1]);
  dprintf(1, "Dizionario letto correttamente.\n");
  correct_input(argv[2], dictionary);
  dprintf(1, "Puoi trovare i risultati in \"%s\".\n", FILE_OUT);

  free_dictionary(dictionary);
}
