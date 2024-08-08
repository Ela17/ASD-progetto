#include <string.h>
#include "../../Unity/unity.h"
#include "../src/lib.h"

void* prova, *expected;

static int a = -10, b=0, c= 10;
#define s1 "Abcd"
#define s2 "aabc"
#define s3 "abcd"
static float f1 = -(float)10.4, f2 = 0.5, f3=(float)15.7;


int compar(const void* a, const void* b){
  return *(int*)a - *(int*)b;
}

int compar2(const void* a, const void* b){
  return strcmp(*(char**)a, *(char**)b);
}

int compar3(const void* a, const void* b){
  if(*(float*)a < *(float*)b) return -1;
  else if(*(float*)a == *(float*)b) return 0;
  else return 1;
}

void setUp(void) {}


void tearDown(void) {
  free(prova);
  free(expected);
}

void test_partition_single_element(void) {
  int prova[1] = {a};
  int expected[1] = {a};
  unsigned long int pivot = partition(prova, 0, 0, compar, sizeof(int));
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 1);
  TEST_ASSERT_EQUAL_UINT(0, pivot);
}

void test_partition_multiple_elements(void) {
  int prova[5] = {5, 3, 8, 4, 2};
  int expected[5] = {4, 3, 2, 5, 8};
  unsigned long int pivot = partition(prova, 0, 4, compar, sizeof(int));

  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 5);

  for (unsigned long int i = 0; i < pivot; i++) {
    TEST_ASSERT_TRUE(prova[i] <= prova[pivot]);
  }
  for (unsigned long int i = pivot + 1; i <= 4; i++) {
    TEST_ASSERT_TRUE(prova[i] > prova[pivot]);
  }

  TEST_ASSERT_EQUAL_UINT(3, pivot);
}

void test_quick_NULL_int(void) {
  int* prova = NULL ;
  quick_sort(prova, 0, sizeof(int), compar);
  
  TEST_ASSERT_NULL(prova);
}

void test_quick_NULL_string(void) {
  char* prova = NULL ;
  quick_sort(prova, 0, sizeof(char*), compar2);
  
  TEST_ASSERT_NULL(prova);
}

void test_quick_NULL_float(void) {
  float* prova = NULL ;
  quick_sort(prova, 0, sizeof(float), compar3);
  
  TEST_ASSERT_NULL(prova);
}

void test_quick_single_elem_int(void) {
  int prova[1] = {a} ;
  int expected[1] = {a} ;
  quick_sort(prova, 1, sizeof(int), compar);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 1);
}

void test_quick_single_elem_string(void) {
  char* prova[1] = {s1} ;
  char* expected[1] = {s1} ;
  quick_sort(prova, 1, sizeof(char*), compar2);
  
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, prova, 1);
}

void test_quick_single_elem_float(void) {
  float prova[1] = {f1} ;
  float expected[1] = {f1} ;
  quick_sort(prova, 1, sizeof(float), compar3);
  
  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, prova, sizeof(float), 1);
}

void test_quick_same_element_int(void) {
  int prova[3] = {a, a, a} ;
  int expected[3] = {a, a, a} ;
  quick_sort(prova, 3, sizeof(int), compar);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 3);
}

void test_quick_same_element_string(void) {
  char* prova[3] = {s1,s1,s1} ;
  char* expected[3] = {s1,s1,s1} ;
  quick_sort(prova, 3, sizeof(char*), compar2);
  
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, prova, 3);
}

void test_quick_same_element_float(void) {
  float prova[3] = {f1,f1,f1} ;
  float expected[3] = {f1,f1,f1} ;
  quick_sort(prova, 3, sizeof(float), compar3);
  
  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, prova, sizeof(float), 3);
}

void test_quick_ordered_int(void) {
  int prova[3] = {a, b, c} ;
  int expected[3] = {a, b, c} ;
  quick_sort(prova, 3, sizeof(int), compar);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 3);
}

void test_quick_ordered_string(void) {
  char* prova[3] = {s1,s2,s3} ;
  char* expected[3] = {s1,s2,s3} ;
  quick_sort(prova, 3, sizeof(char*), compar2);
  
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, prova, 3);
}

void test_quick_ordered_float(void) {
  float prova[3] = {f1,f2,f3} ;
  float expected[3] = {f1,f2,f3} ;
  quick_sort(prova, 3, sizeof(float), compar3);
  
  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, prova, sizeof(float), 3);
}

void test_quick_opposite_order_int(void) {
  int prova[3] = {c,b,a} ;
  int expected[3] = {a, b, c} ;
  quick_sort(prova, 3, sizeof(int), compar);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 3);
}

void test_quick_opposite_order_string(void) {
  char* prova[3] = {s3,s2,s1} ;
  char* expected[3] = {s1,s2,s3} ;
  quick_sort(prova, 3, sizeof(char*), compar2);

  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, prova, 3);
}

void test_quick_opposite_order_float(void) {
  float prova[3] = {f3,f2,f1} ;
  float expected[3] = {f1,f2,f3} ;
  quick_sort(prova, 3, sizeof(float), compar3);
  
  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, prova, sizeof(float), 3);
}

void test_merge_two_elements(void) {
  int prova[2] = {b, a};
  int expected[2] = {a, b};
  merge(prova, sizeof(int), compar, 0, 1, 1);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 2);
}

void test_merge_multiple_elements(void) {
  int prova[6] = {1, 3, 5, 2, 4, 6};
  int expected[6] = {1, 2, 3, 4, 5, 6};
  merge(prova, sizeof(int), compar, 0, 3, 5);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 6);
}

void test_merge_NULL_int(void) {
  int* prova = NULL ;
  merge_sort(prova, 0, sizeof(int), compar);
  
  TEST_ASSERT_NULL(prova);
}

void test_merge_NULL_string(void) {
  char* prova = NULL ;
  merge_sort(prova, 0, sizeof(char*), compar2);
  
  TEST_ASSERT_NULL(prova);
}

void test_merge_NULL_float(void) {
  float* prova = NULL ;
  merge_sort(prova, 0, sizeof(float), compar3);
  
  TEST_ASSERT_NULL(prova);
}

void test_merge_single_elem_int(void) {
  int prova[1] = {a} ;
  int expected[1] = {a} ;
  merge_sort(prova, 1, sizeof(int), compar);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 1);
}

void test_merge_single_elem_string(void) {
  char* prova[1] = {s1} ;
  char* expected[1] = {s1} ;
  merge_sort(prova, 1, sizeof(char*), compar2);
  
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, prova, 1);
}

void test_merge_single_elem_float(void) {
  float prova[1] = {f1} ;
  float expected[1] = {f1} ;
  merge_sort(prova, 1, sizeof(float), compar3);
  
  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, prova, sizeof(float), 1);
}

void test_merge_same_element_int(void) {
  int prova[3] = {a, a, a} ;
  int expected[3] = {a, a, a} ;
  merge_sort(prova, 3, sizeof(int), compar);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 3);
}

void test_merge_same_element_string(void) {
  char* prova[3] = {s1,s1,s1} ;
  char* expected[3] = {s1,s1,s1} ;
  merge_sort(prova, 3, sizeof(char*), compar2);
  
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, prova, 3);
}

void test_merge_same_element_float(void) {
  float prova[3] = {f1,f1,f1} ;
  float expected[3] = {f1,f1,f1} ;
  merge_sort(prova, 3, sizeof(float), compar3);
  
  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, prova, sizeof(float), 3);
}

void test_merge_ordered_int(void) {
  int prova[3] = {a, b, c} ;
  int expected[3] = {a, b, c} ;
  merge_sort(prova, 3, sizeof(int), compar);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 3);
}

void test_merge_ordered_string(void) {
  char* prova[3] = {s1,s2,s3} ;
  char* expected[3] = {s1,s2,s3} ;
  merge_sort(prova, 3, sizeof(char*), compar2);
  
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, prova, 3);
}

void test_merge_ordered_float(void) {
  float prova[3] = {f1,f2,f3} ;
  float expected[3] = {f1,f2,f3} ;
  merge_sort(prova, 3, sizeof(float), compar3);
  
  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, prova, sizeof(float), 3);
}

void test_merge_opposite_order_int(void) {
  int prova[3] = {c,b,a} ;
  int expected[3] = {a, b, c} ;
  merge_sort(prova, 3, sizeof(int), compar);
  
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, prova, 3);
}

void test_merge_opposite_order_string(void) {
  char* prova[3] = {s3,s2,s1} ;
  char* expected[3] = {s1,s2,s3} ;
  merge_sort(prova, 3, sizeof(char*), compar2);
  
  TEST_ASSERT_EQUAL_STRING_ARRAY(expected, prova, 3);
}

void test_merge_opposite_order_float(void) {
  float prova[3] = {f3,f2,f1} ;
  float expected[3] = {f1,f2,f3} ;
  merge_sort(prova, 3, sizeof(float), compar3);
  
  TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, prova,sizeof(float), 3);
}


int main(void) {
  UNITY_BEGIN();
  
  RUN_TEST(test_partition_single_element);
  RUN_TEST(test_partition_multiple_elements);

  RUN_TEST(test_quick_NULL_int);
  RUN_TEST(test_quick_NULL_string);
  RUN_TEST(test_quick_NULL_float);
  RUN_TEST(test_quick_single_elem_int);
  RUN_TEST(test_quick_single_elem_string);
  RUN_TEST(test_quick_single_elem_float);
  RUN_TEST(test_quick_same_element_int);
  RUN_TEST(test_quick_same_element_string);
  RUN_TEST(test_quick_same_element_float);
  RUN_TEST(test_quick_ordered_int);
  RUN_TEST(test_quick_ordered_string);
  RUN_TEST(test_quick_ordered_float);
  RUN_TEST(test_quick_opposite_order_int);
  RUN_TEST(test_quick_opposite_order_string);
  RUN_TEST(test_quick_opposite_order_float);    

  RUN_TEST(test_merge_two_elements);
  RUN_TEST(test_merge_multiple_elements);
  
  RUN_TEST(test_merge_NULL_int);
  RUN_TEST(test_merge_NULL_string);
  RUN_TEST(test_merge_NULL_float);
  RUN_TEST(test_merge_single_elem_int);
  RUN_TEST(test_merge_single_elem_string);
  RUN_TEST(test_merge_single_elem_float);
  RUN_TEST(test_merge_same_element_int);
  RUN_TEST(test_merge_same_element_string);
  RUN_TEST(test_merge_same_element_float);
  RUN_TEST(test_merge_ordered_int);
  RUN_TEST(test_merge_ordered_string);
  RUN_TEST(test_merge_ordered_float);
  RUN_TEST(test_merge_opposite_order_int);
  RUN_TEST(test_merge_opposite_order_string);
  RUN_TEST(test_merge_opposite_order_float); 
  
  return UNITY_END();
}
