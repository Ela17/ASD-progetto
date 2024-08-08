#include "./lib.h"
#include "./utils.h"
#include "./EXIT_MACRO.h"
#include <string.h>
#include <time.h>

size_t n_items = 0, arr_size = 1;

typedef struct _record{
  long field0;
  char* field1;
  int field2;
  double field3;
}record;

record* create_array();
record* enlarge_array(record* arr);

record* retrieve_array(record* rcd, FILE* infile);
record retrieve_line(record* rcd, char* line_buffer);

void alg_choice(size_t alg, size_t field, record* base);

int compar1(const void* a, const void* b);
int compar2(const void* a, const void* b);
int compar3(const void* a, const void* b);

void write_on_file(record* rcd, FILE* outfile);



void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo){

  record* rcd = create_array();

  rcd = retrieve_array(rcd, infile);

  dprintf(1, "creato array di %li elementi\n", n_items);
  
  double start = (double)clock();
  alg_choice(algo, field, rcd);
  double time_spent = ((double)clock() - start) / CLOCKS_PER_SEC;

  dprintf(1, "ordinato array con algoritmo %s in %f secondi\n", algo == 1 ? "merge sort" : "quick sort", time_spent);
  
  write_on_file(rcd, outfile);
  
  dprintf(1, "scritto su file\n");
}

record* retrieve_array(record* rcd, FILE* infile){

  char* line_buffer = malloc(BUF_LEN);
  

  while(fgets(line_buffer, BUF_LEN, infile) != NULL){

      if(arr_size == n_items){
        rcd = enlarge_array(rcd);
      }

      rcd[n_items] = retrieve_line(rcd, line_buffer);
      
      n_items++;
    }
    
    free(line_buffer);
    return rcd;
}

record retrieve_line(record* rcd, char* line_buffer){
  char* control = "";
  char* field_buffer = malloc(BUF_LEN);
  
  strcpy(field_buffer, strtok(line_buffer, ","));
  rcd[n_items].field0 = atol(field_buffer);
  
  strcpy(field_buffer, strtok(NULL, ","));    
  rcd[n_items].field1 = malloc(strlen(field_buffer)+1);
  strcpy(rcd[n_items].field1, field_buffer);
  
  strcpy(field_buffer, strtok(NULL, ","));
  rcd[n_items].field2 = atoi(field_buffer);
  
  strcpy(field_buffer, strtok(NULL, ","));
  rcd[n_items].field3 = (double)strtod(field_buffer, &control);
  if(control[0] != '\0') EXIT_ON_ERROR
  
  free(field_buffer);
  return rcd[n_items];
}


void control_argc(int argc){
  if(argc < N_PARAM) {
    dprintf(2,"Too few arguments, expexted \"FILE_in\", \"FILE_out\", \"field\", \"sorting algorithm\".");
    exit(EXIT_FAILURE);
  }

  if(argc > N_PARAM) {
    dprintf(2,"Too many arguments, expexted \"FILE_in\", \"FILE_out\", \"field\", \"sorting algorithm\".");
    exit(EXIT_FAILURE);
  }
}

parameters retrieve_parameters(char* argv[]){
  parameters par;
  strcpy(par.csv_in, argv[1]);
  strcpy(par.csv_out, argv[2]);
  
  par.field = strtoul(argv[3], NULL, 0);
  par.alg = strtoul(argv[4], NULL, 0);
  
  return par;
}


record* create_array(){
  return calloc(1, sizeof(record));
}

record* enlarge_array(record* arr){
  arr_size = arr_size*2;
  return realloc(arr, arr_size*sizeof(record));
}



void alg_choice(size_t alg, size_t field, record* base){
  switch(field){
    case 1:
      if(alg == 1) merge_sort(base, n_items, sizeof(record), compar1);
      else if(alg == 2) quick_sort(base, n_items, sizeof(record), compar1);
      else{
        dprintf(2, "Invalid argument for sorting algorithm.\n");
        exit(EXIT_FAILURE);
      } 
      break;
    case 2:
      if(alg == 1) merge_sort(base, n_items, sizeof(record), compar2);
      else if(alg == 2) quick_sort(base, n_items, sizeof(record), compar2);
      else{
        dprintf(2, "Invalid argument for sorting algorithm.\n");
        exit(EXIT_FAILURE);
      } 
      break;
    case 3:
      if(alg == 1) merge_sort(base, n_items, sizeof(record), compar3);
      else if(alg == 2) quick_sort(base, n_items, sizeof(record), compar3);
      else{
        dprintf(2, "Invalid argument for sorting algorithm.\n");
        exit(EXIT_FAILURE);
      } 
      break;
    default:
      dprintf(2, "Invalid argument for field.\n");
      exit(EXIT_FAILURE);
  }
}

int compar1(const void* a, const void* b){
	return strcmp((*(record*)a).field1, (*(record*)b).field1);
}

int compar2(const void* a, const void* b){
  record arg1 = *(record*)a;
  record arg2 = *(record*)b;
	return (arg1.field2 - arg2.field2);
}

int compar3(const void* a, const void* b){
  record arg1 = *(record*)a;
  record arg2 = *(record*)b;

	if(arg1.field3 < arg2.field3) return -1;
	else if(arg1.field3 == arg2.field3) return 0;
	else return 1;
}

void write_on_file(record* rcd, FILE* outfile){
  for(size_t i = 0; i < n_items; i++){
    fprintf(outfile, "%li,", rcd[i].field0);
    fprintf(outfile, "%s,", rcd[i].field1);
    fprintf(outfile, "%i,", rcd[i].field2);
    fprintf(outfile, "%f\n", rcd[i].field3);
    free(rcd[i].field1);
  }
  free(rcd);
}

void main_clean(FILE* in, FILE* out){
  fclose(in);
  fclose(out);
}
