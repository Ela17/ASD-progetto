#include "./utils.h"

int main(int argc, char* argv[]){
  control_argc(argc);

  parameters par = retrieve_parameters(argv);

  FILE* fp_in = fopen(par.csv_in, "r");
  FILE* fp_out = fopen(par.csv_out, "w");

  sort_records(fp_in, fp_out, par.field, par.alg);

  main_clean(fp_in, fp_out);
}










