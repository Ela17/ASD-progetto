#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


#define EXIT_ON_ERROR {if (errno) {fprintf(stderr,  \
  " line %d: pid %ld; errno: %d (%s)\n",     \
  __LINE__,                            \
  (long) getpid(),                     \
  errno,                               \
  strerror(errno));  exit(EXIT_FAILURE);}}
  