
#ifndef EX1_H_ohuahudwwdipawjdjdiawdsdogpeh
#define EX1_H_ohuahudwwdipawjdjdiawdsdogpeh

#include <stdlib.h>
  
/** 
 * It partitions the array passed using the 'base' parameter. It takes the first element as pivot and places it in the correct position in the array.
 * It returns the index of the pivot.
 * 
 * @param base pointer to the first element of the array
 * @param nitems number of items contained in the 'base' array
 * @param size the size of the TYPE of elements contained by the 'base' array
 * @param end the last index of the array
 * @param (*compar) the comparing function
 */
unsigned long int partition(void* base, unsigned long int start, unsigned long int end, int (*compar)(const void*, const void*), size_t size);

/**
  * It uses a 'Quick sort' based algorithm to sort the array passed using the 'base' parameter.
  * It doesn't return anything, on error it terminates the execution using "exit(EXIT_FAILURE)" 
  * and writes in the sterror the error number and the plausible cause of the error.
  * @param base pointer to the first element of the array 
  * @param nitems number of items contained in the 'base' array
  * @param size the size of the TYPE of elements contained by the 'base' array
  * @param (*compar) the comparing function: int (*compar)(const void*, const void*)) It is used in order to sort the array. It must return:
  *                       - any value < 0 if the first element is lower than the second;
  *                       - exactly 0 if the two elements are equals;
  *                       - any value > 0 if the first element is higher than the second.
  *                       
*/  	
  void quick_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*));


/**
 * It merges the two sorted arrays in the array passed using the 'base' parameter.
 * 
 * @param base pointer to the first element of the array
 * @param size the size of the TYPE of elements contained by the 'base' array
 * @param (*compar) the comparing function
 * @param start the first index of the array
 * @param mid the middle index of the array
 */
void merge(void* base, size_t size, int (*compar)(const void*, const void*), unsigned long int start, unsigned long int mid, unsigned long int end);

/**
  * It uses a 'Merge sort' based algorithm to sort the array passed using the 'base' parameter.
  * It doesn't return anything, on error it terminates the execution using "exit(EXIT_FAILURE)" 
  * and writes in the sterror the error number and the plausible cause of the error.
  * @param base pointer to the first element of the array 
  * @param nitems number of items contained in the 'base' array
  * @param size the size of the TYPE of elements contained by the 'base' array
  * @param (*compar) the comparing function: int (*compar)(const void*, const void*)) It is used in order to sort the array. It must return:
  *                       - any value < 0 if the first element is lower than the second;
  *                       - exactly 0 if the two elements are equals;
  *                       - any value > 0 if the first element is higher than the second.
  *                       
*/ 
  void merge_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*));


#endif
