#include "utils.h"
#include "EXIT_MACRO.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define BUF_LEN 256
#define N_PARAM 3

size_t n_items = 0, arr_size = 1;

/**
 * @brief Allocate memory for an array of strings.
 *
 * This function allocates memory for an array of strings with initial capacity.
 *
 * @return A pointer to the allocated memory.
 */
char** create_array();

/**
 * @brief Increase the size of an array of strings.
 *
 * This function increases the size of an array of strings by doubling its capacity.
 *
 * @param arr Pointer to the array of strings.
 * @return A pointer to the reallocated memory.
 */
char** enlarge_array(char** arr);

/**
 * @brief Iterative function to find the minimum edit distance between a buffer and a set of words in a dictionary.
 *
 * This function computes the minimum edit distance between the base string (buf) and each word in the dictionary (dictry).
 *
 * @param dictry An array of pointers to strings representing the dictionary of words to compare with buf.
 * @param buf The base string to compare with words in the dictionary.
 * @param values An array containing the edit distances computed for all words in the dictionary.
 * @return The minimum value in the values array.
 */
int find_min_edit_distance(char** dictry, char* buf, int* values);

/**
 * @brief Converts a string to lowercase alphabetic characters and truncates at the first non-alphabetic character.
 *
 * The function elides the first non-alphabetics characters and truncates the string at the first non-alphabetic character encountered, 
 * effectively removing any non-alphabetic characters and terminating the string.
 *
 * @param str The string to be converted to lowercase and truncated.
 * @return The new value of the string.
 */
char* to_alphabetic_lowercase(char* str);


/**
 * @brief Iterative function to check the minimum edit_distance of the current word of the input text file.
 *
 * This function converts the current word that is being checked(buffer) in lowercase and calls the 'find_min_edit_distance' function to compute the minimum edit distance with all  
 * the words in the database(dictionary). It then checks the values stored in the array(values) in order to print all the matching results in the output file(f_out).
 *
 * @param dictionary An array of pointers to strings representing the dictionary of words to compare with buf.
 * @param buffer The base string to compare with words in the dictionary.
 * @param values An array containing the edit distances computed for all words in the dictionary.
 * @param f_out The file chosen to write the results in.
 */
void check_word(char** dictionary, char* buffer, int* values, FILE* f_out);



void control_argc(int argc){
  if(argc < N_PARAM) {
    dprintf(2,"Too few arguments, expexted \"FILE_dictionary\", \"FILE_to_correct\".");
    exit(EXIT_FAILURE);
  }
  if(argc > N_PARAM) {
    dprintf(2,"Too many arguments, expexted \"FILE_dictionary\", \"FILE_to_correct\".");
    exit(EXIT_FAILURE);
  }
}


char** create_array(){
  char** arr = calloc(arr_size, sizeof(char*));
  if(arr == NULL) EXIT_ON_ERROR
  return arr;
}


char** enlarge_array(char** arr) {
  arr_size *= 2;
  char** new_arr = realloc(arr, arr_size * sizeof(char*));
  if (new_arr == NULL) {
    EXIT_ON_ERROR
  }
  return new_arr;
}


char** read_dictionary(char* file_in){
  FILE* fp = fopen(file_in, "r");

  if(fp == NULL) EXIT_ON_ERROR

  char** dictionary = create_array();
  
  char* buffer = malloc(BUF_LEN);
  if (buffer == NULL) {
    fclose(fp);
    free(dictionary);
    EXIT_ON_ERROR
  }

  while(fscanf(fp, "%s", buffer) != EOF) {
    if(arr_size == n_items){
      dictionary = enlarge_array(dictionary);
    }

    size_t buf_size = strlen(buffer) + 1;
    dictionary[n_items] = calloc(buf_size, sizeof(char));
    if (dictionary[n_items] == NULL) {
      fclose(fp);
      free(buffer);
      free_dictionary(dictionary);
      EXIT_ON_ERROR
    }

    strcpy(dictionary[n_items], buffer);
    n_items++;
  }

  fclose(fp);
  free(buffer);
  return dictionary;
}


void correct_input(char* file_in, char** dictionary) {
  FILE* f_in = fopen(file_in, "r");
  FILE* f_out = fopen(FILE_OUT, "w");
  if(f_in== NULL || f_out == NULL) EXIT_ON_ERROR

  int* values = calloc(n_items, sizeof(int));
  char* buffer = malloc(BUF_LEN);
  
  if (values == NULL || buffer == NULL) {
    fclose(f_in);
    fclose(f_out);
    free(values);
    free(buffer);
    EXIT_ON_ERROR
  }

  while(fscanf(f_in, "%s", buffer) != EOF) {
    check_word( dictionary,  buffer, values,f_out);
  }

  free(buffer);
  free(values);
  fclose(f_in);
  fclose(f_out);
}




void check_word(char** dictionary, char* buffer, int* values, FILE* f_out){
  buffer = to_alphabetic_lowercase(buffer);
  
  if(strlen(buffer) > 0){ 
    int min = find_min_edit_distance(dictionary, buffer, values);

    fprintf(f_out, "%s -> min edit distance = %d\n", buffer, min);
    for(size_t i = 0; i < n_items; i++){
      if(values[i] == min) {
        fprintf(f_out, "\t%s\n", dictionary[i]);
        if(min == 0) break;
      }
    }
    fprintf(f_out, "\n");
  }
}


int find_min_edit_distance(char** dictry, char* buf, int* values) {
  int min_value = INT_MAX;

  for (size_t i = 0; i < n_items; i++) {
    values[i] = edit_distance_dyn(dictry[i], buf);
    if(values[i] == 0) return 0;

    if (values[i] < min_value)
      min_value = values[i];
  }

  return min_value;
}



char* to_alphabetic_lowercase(char* str) {
  size_t len = strlen(str);
  int flag = 0;
  
  for(size_t i = 0; i < len; i++) {
    if(!isalpha(str[i])){
    
      if(!flag){
        str = str+1;
        i--; len--;
      }
      else{
        str[i] = '\0';
        return str;
      }
    }
    else{
      flag++;
      str[i] = (char)tolower(str[i]);
    }
  }
  return str;
}




void free_dictionary(char** dictionary) {
  for (size_t i = 0; i < n_items; i++) {
    free(dictionary[i]);
  }
  free(dictionary);
}
