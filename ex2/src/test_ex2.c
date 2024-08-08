#include <stdlib.h>
#include <string.h>
#include "../../Unity/unity.h"
#include "../src/lib.h"

int result;

#define s1 "casa"
#define s2 "vinaio"
#define s3 "tassa"

void setUp(void) {
    
}

void tearDown(void) {
    
}

void test_distance_NULL(void) {
  result = edit_distance(NULL, s1);
  TEST_ASSERT_EQUAL_INT(-1, result);
}

void test_distance_both_NULL(void) {
  result = edit_distance_dyn(NULL, NULL);
  TEST_ASSERT_EQUAL_INT(-1, result);
}

void test_distance_both_empty(void) {
  result = edit_distance_dyn("", "");
  TEST_ASSERT_EQUAL_INT(0, result);
}

void test_distance_empty_string(void) { 
  result = edit_distance("", s1);  
  TEST_ASSERT_EQUAL_INT(strlen(s1), result);
}

void test_distance_same_string(void) {
  result = edit_distance(s1, s1);
  TEST_ASSERT_EQUAL_INT(0, result);
}

void test_distance_normal1(void) { 
  result = edit_distance(s1, "cassa");
  TEST_ASSERT_EQUAL_INT(1, result);
}

void test_distance_normal2(void) {
  result = edit_distance(s1, "cara");
  TEST_ASSERT_EQUAL_INT(2, result);
}

void test_distance_normal3(void) {
  result = edit_distance(s2, "vino");
  TEST_ASSERT_EQUAL_INT(2, result);
}

void test_distance_normal4(void) {
  result = edit_distance(s3, "passato");
  TEST_ASSERT_EQUAL_INT(4, result);
}

void test_distance_different_length_strings(void) {
  result = edit_distance_dyn(s1, s3);
  TEST_ASSERT_EQUAL_INT(3, result);
}

void test_distance_whitespace_strings(void) {
  result = edit_distance("   ", "   ");
  TEST_ASSERT_EQUAL_INT(0, result);
}

void test_distance_single_char_strings(void) {
  result = edit_distance("a", "a");
  TEST_ASSERT_EQUAL_INT(0, result);

  result = edit_distance("a", "b");
  TEST_ASSERT_EQUAL_INT(2, result);
}


int main(void) {
  UNITY_BEGIN();
    
  RUN_TEST(test_distance_NULL);
  RUN_TEST(test_distance_both_NULL);
  RUN_TEST(test_distance_empty_string);
  RUN_TEST(test_distance_both_empty);
  RUN_TEST(test_distance_same_string);
  RUN_TEST(test_distance_normal1);
  RUN_TEST(test_distance_normal2);
  RUN_TEST(test_distance_normal3);
  RUN_TEST(test_distance_normal4);
  RUN_TEST(test_distance_different_length_strings);
  RUN_TEST(test_distance_whitespace_strings);
  RUN_TEST(test_distance_single_char_strings);

  return UNITY_END();
}
