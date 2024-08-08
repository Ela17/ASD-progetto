#include "lib.h"
#include "EXIT_MACRO.h"
#include <stdlib.h>
#include <string.h>
	
/**
 * Sorts the array passed using the 'base' parameter. It uses the 'Quick sort' algorithm.
 * 
 * @param base pointer to the first element of the array
 * @param nitems number of items contained in the 'base' array
 * @param size the size of the TYPE of elements contained by the 'base' array
 * @param (*compar) the comparing function
 * @param start the first index of the array
 * @param end the last index of the array
 */
void quick_sort_wrapped(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*), unsigned long int start, unsigned long int end);

/**
 * It swaps the elements at the indexes 'i' and 'j' in the array passed using the 'base' parameter.
 * 
 * @param base pointer to the first element of the array
 * @param i the first index
 * @param j the second index
 * @param size the size of the TYPE of elements contained by the 'base' array
 */
void swap(void* base, unsigned long int i, unsigned long int j, size_t size);

/**
 * Sorts the array passed using the 'base' parameter. It uses the 'Merge sort' algorithm.
 * 
 * @param base pointer to the first element of the array
 * @param nitems number of items contained in the 'base' array
 * @param size the size of the TYPE of elements contained by the 'base' array
 * @param (*compar) the comparing function
 * @param start the first index of the array
 * @param end the last index of the array
 */
void merge_sort_wrapped(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*), unsigned long int start, unsigned long int end);


void quick_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*)){
  quick_sort_wrapped(base, nitems, size, compar, 0, nitems-1);
}


void quick_sort_wrapped(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*), unsigned long int start, unsigned long int end){
  unsigned long int pivot;

  if(nitems > 1){
    pivot = partition(base, start, end, compar, size);

    quick_sort_wrapped(base, pivot-start, size, compar, start, pivot-1); 
    quick_sort_wrapped(base, end-pivot, size, compar, pivot+1, end); 
  }
}


unsigned long int partition(void* base, unsigned long int start, unsigned long int end, int (*compar)(const void*, const void*), size_t size){
  unsigned long int i = end, j = end;

  while(i > start){
    if(compar(base + (i*size), base + (start*size)) > 0){
        if(i != j) swap(base, i, j, size);
        j--;
      }
    i--;
  }

  swap(base, start, j, size);
  return j;
}


void swap(void* base, unsigned long int i, unsigned long int j, size_t size){
  void* pivot;
  if((pivot = malloc(size)) == NULL && size != 0) EXIT_ON_ERROR;

  memcpy(pivot, base+(i*size), size);

  memcpy(base+(i*size),base+(j*size), size);

  memcpy(base+(j*size), pivot, size);

  free(pivot);
}


void merge_sort(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*)){
  merge_sort_wrapped(base, nitems, size, compar, 0, nitems-1);
}


void merge_sort_wrapped(void* base, size_t nitems, size_t size, int (*compar)(const void*, const void*), unsigned long int start, unsigned long int end){
  unsigned long int m = 0;

  if(nitems > 1){
    m = (nitems/2) + start;

    merge_sort_wrapped(base, nitems/2, size, compar, start, start+((nitems/2)-1));

    merge_sort_wrapped(base, (nitems/2)+(nitems%2), size, compar, start+(nitems/2), end);

    merge(base, size, compar, start, m, end);

  }
}


void merge(void* base, size_t size, int (*compar)(const void*, const void*), unsigned long int start, unsigned long int mid, unsigned long int end){
  unsigned long int i = start, j=mid, k=0, calloc_value = (end-start)+1;
  
  void* temp;
  if((temp = calloc(calloc_value, size)) == NULL && (calloc_value + size) != 0) EXIT_ON_ERROR

  while(i < mid && j <= end){
    if(compar(base+(i*size), base+(j*size)) <= 0){
      memcpy(temp+(k*size), base+(i*size), size);
      i++;
    }
    else{
      memcpy(temp+(k*size), base+(j*size), size);
      j++;
    }
    k++;
  }

  if(i < mid){
    memcpy(temp+(k*size), base+(i*size), size*(mid-i));
  }
  else{
    memcpy(temp+(k*size), base+(j*size), size*((end+1)-j));
  }

  memcpy(base+(start*size), temp, size*(end-start+1));
  
  free(temp);
}
