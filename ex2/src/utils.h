#ifndef UTILS_H_hcjhhjmvm
#define UTILS_H_hcjhhjmvm

#include "lib.h"
#define FILE_OUT "./results.txt"

/**
 * @brief Check the number of command-line arguments.
 *
 * This function verifies if the correct number of command-line arguments is provided.
 * If not, it prints an error message and exits the program.
 *
 * @param argc Number of command-line arguments.
 */
void control_argc(int argc);

/**
 * @brief Read the dictionary from a file.
 *
 * This function reads words from a file and stores them in an array of strings.
 *
 * @param file_in Name of the input file containing the dictionary.
 * @return A pointer to the array of strings containing the dictionary.
 */
char** read_dictionary(char* file_dictry);

/**
 * @brief Correct the input text based on the dictionary.
 *
 * This function reads the input text, computes the minimum edit distance between each word
 * in the dictionary and the input text, and writes the corrected text to an output file.
 *
 * @param file_in Name of the input file containing the text to be corrected.
 * @param dictionary Array of strings representing the dictionary.
 */
void correct_input(char* file_in, char** dictionary);

/**
 * @brief Free the memory allocated for the dictionary.
 *
 * This function frees the memory allocated for the array of strings representing the dictionary.
 *
 * @param dictionary Array of strings representing the dictionary.
 */
void free_dictionary(char** dictionary);

#endif
