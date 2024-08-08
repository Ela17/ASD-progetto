#include <stdlib.h>
#include <stdio.h>

#ifndef UTILS_EX1_oadhaoidhwbfjefuh
#define UTILS_EX1_oadhaoidhwbfjefuh

#define PATH_LEN 256
#define N_PARAM 5
#define BUF_LEN 1024

/**
 * Structure that contains the parameters passed to the program.
 */
typedef struct _parameters{
  char csv_in[PATH_LEN];
  char csv_out[PATH_LEN];
  size_t field;
  size_t alg;
}parameters;

/**
 * It reads the file passed using the 'infile' parameter and writes the sorted records in the file passed using the 'outfile' parameter.
 * 
 * @param infile pointer to the file to read
 * @param outfile pointer to the file to write
 * @param field the field to sort
 * @param algo the algorithm to use
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);

/**
 * It checks if the number of arguments passed to the program is correct.
 * 
 * @param argc the number of arguments passed to the program
 */
void control_argc(int argc);

/**
 * It retrieves the parameters passed to the program.
 * 
 * @param argv the arguments passed to the program
 */
parameters retrieve_parameters(char* argv[]);

/**
 * It cleans the memory and closes the files.
 */
void main_clean(FILE* in, FILE* out);


#endif







