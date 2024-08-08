#ifndef EX2_H_jghlergheslghesoighslkkfhnseiourfh
#define EX2_H_jghlergheslghesoighslkkfhnseiourfh

/**
 * @brief Calculates the edit distance between two strings.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * 
 * @return The edit distance between the two strings. If any of the strings is NULL, returns -1.
 */
int edit_distance(const char *s1, const char* s2);

/**
 * @brief Calculates the edit distance between two strings using memoization.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 *
 * @return The edit distance between the two strings. If any of the strings is NULL, returns -1.
*/
int edit_distance_dyn(const char *s1, const char* s2);

#endif



