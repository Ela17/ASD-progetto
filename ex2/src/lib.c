#include "lib.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "EXIT_MACRO.h"

/**
 * @brief Returns the string passed as parameter without the first character.
 * 
 * @param str The string to process.
 * 
 * @return The string passed as parameter without the first character.
 */
char* rest(const char* str);

/**
 * @brief Returns the minimum value between the three passed as parameters.
 * 
 * @param s1 The first value.
 * @param s2 The second value.
 * @param s3 The third value.
 * 
 * @return The minimum value between the three passed as parameters.
 */
int minimum(int s1, int s2, int s3);

/**
 * @brief Calculates the edit distance between two strings.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param distance_table The table to store the results of the subproblems.
 * 
 * @return The edit distance between the two strings. If any of the strings is NULL, returns -1.
 */
int edit_distance_dyn_wrappered(const char *s1, const char* s2, int** distance_table);

/**
 * @brief Builds a table of integers.
 * 
 * @param rows The number of rows of the table.
 * @param cols The number of columns of the table.
 * 
 * @return The table of integers.
 */
int** build_table(size_t rows, size_t cols);

/**
 * @brief Searches the table for the value of the subproblem.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param table The table to search.
 * 
 * @return The value of the subproblem if found, -1 otherwise.
 */
int search_memo(const char *s1, const char* s2, int** table);

/**
 * @brief Inserts the value of the subproblem in the table.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param table The table to insert the value.
 * @param value The value to insert.
 */
void insert_memo(const char *s1, const char* s2, int** table, int value);

/**
 * @brief Frees the memory allocated for the table.
 * 
 * @param table The table to free.
 * @param rows The number of rows of the table.
 */
void free_table(int** table, int rows);


int edit_distance(const char *s1, const char* s2){

  if(s1 == NULL || s2 == NULL) return -1;

  int length1 = (int)strlen(s1), length2 = (int)strlen(s2);
  if(length1 == 0) return length2;
  if(length2 == 0) return length1;
  
  int d_no_op, d_canc, d_ins;
  d_no_op = (s1[0] == s2[0]) ?  edit_distance(rest(s1), rest(s2)) : INT_MAX ;
  d_canc = 1 + edit_distance(s1, rest(s2));
  d_ins = 1 + edit_distance(rest(s1), s2);
  
  return minimum(d_no_op, d_canc, d_ins);
}


char* rest(const char* str){
  return (char*)str+1;
}


int minimum(int s1, int s2, int s3){
  if(s1 < s2){
    if(s1 < s3) return s1;
    else return s3;
  }
  else if(s2 < s3) return s2;
  else return s3;
}


int edit_distance_dyn(const char *s1, const char* s2){
  if(s1 == NULL || s2 == NULL) return -1;

  size_t length1 = strlen(s1);
  size_t length2 = strlen(s2);

  int** distance_table = build_table(length1, length2);
  int result = edit_distance_dyn_wrappered(s1, s2, distance_table);
  free_table(distance_table, (int)length1);
  return result;
}


int edit_distance_dyn_wrappered(const char *s1, const char* s2, int** memo){
  if(s1 == NULL || s2 == NULL || memo == NULL) return -1;

  int length1 = (int)strlen(s1);
  int length2 = (int)strlen(s2);

  if(length1 == 0) return length2;

  if(length2 == 0) return length1;

  int found = search_memo(s1, s2, memo);
  if(found != -1) return found;

  int d_no_op, d_canc, d_ins;

  if(s1[0] == s2[0]){
    d_no_op =  edit_distance_dyn_wrappered(rest(s1), rest(s2), memo);
    d_canc = INT_MAX;
    d_ins = INT_MAX;
  }
  else{
    d_no_op = INT_MAX ;
    d_canc = 1 + edit_distance_dyn_wrappered(s1, rest(s2), memo);
    d_ins = 1 + edit_distance_dyn_wrappered(rest(s1), s2, memo);
  }

  int current_dist = minimum(d_no_op, d_canc, d_ins);

  insert_memo(s1, s2, memo, current_dist);

  return current_dist;
}


int** build_table(size_t rows, size_t cols){
  int** table = (int**)malloc((rows+1) * sizeof(int*));
  if(table == NULL) exit(EXIT_FAILURE);

  for(size_t i = 0; i <= rows; i++){
    table[i] = (int*)malloc((cols+1) * sizeof(int));
    if(table[i] == NULL) exit(EXIT_FAILURE);
  }

  for(size_t i = 0; i <= rows; i++){
    for(size_t j = 0; j <= cols; j++){
      table[i][j] = -1;
    }
  }

  return table;
}


int search_memo(const char *s1, const char* s2, int** table) {
  if(s1 == NULL || s2 == NULL || table == NULL) return -1;
  int length1 = (int)strlen(s1);
  int length2 = (int)strlen(s2);

  if(table[length1][length2] != -1) return table[length1][length2];
  return -1;
}


void insert_memo(const char *s1, const char* s2, int** table, int value) {
  if(s1 == NULL || s2 == NULL || table == NULL || value < 0) return;
  int length1 = (int)strlen(s1);
  int length2 = (int)strlen(s2);
  table[length1][length2] = value;
}


void free_table(int** table, int rows) {
  for(int i = 0; i <= rows; i++){
    free(table[i]);
  }
  free(table);
}
