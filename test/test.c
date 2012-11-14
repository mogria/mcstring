#include <mcstring/mcstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define MCASSERT_MAX_ERROR_LENGTH 255
#define MCASSERT_INIT \
  char **_mc_assert_errorbuffer = NULL; \
  unsigned int _mc_assert_num_ok = 0; \
  unsigned int _mc_assert_num_fail = 0

#define MCASSERT(condition) do { \
  if(condition) { \
    puts(" [OK]"); \
    _mc_assert_num_ok++; \
  } else { \
    puts(" [FAIL]"); \
    _mc_assert_num_fail++; \
    _mc_assert_errorbuffer = realloc(_mc_assert_errorbuffer, _mc_assert_num_fail * sizeof(char*)); \
    _mc_assert_errorbuffer[_mc_assert_num_fail - 1] = malloc(sizeof(char) * MCASSERT_MAX_ERROR_LENGTH);\
    snprintf(_mc_assert_errorbuffer[_mc_assert_num_fail - 1], MCASSERT_MAX_ERROR_LENGTH, "%s:%i assertion `%s` fails\n", __FILE__, __LINE__,  #condition); \
  } \
} while(0)

#define MCASSERT_SUMMARY do { \
  if(_mc_assert_num_fail > 0) { \
    printf("\nFAIL: %i assertions. %i ok, %i fails.\n", _mc_assert_num_ok + _mc_assert_num_fail, _mc_assert_num_ok, _mc_assert_num_fail); \
    int x; \
    for(x = 0; x < _mc_assert_num_fail; x++) { \
      printf("%s", _mc_assert_errorbuffer[x]); \
    } \
  } else { \
    printf("OK: %i assertions.", _mc_assert_num_ok); \
  } \
} while(0)

#define MCASSERT_RETURN_STATUS _mc_assert_num_fail > 0 ? EXIT_FAILURE : EXIT_SUCCESS;

int main(int argc, char **argv) {

  MCASSERT_INIT;

  printf("checking wheter string initializes correctly");
  mcstring *str = new_string("initial value");
  MCASSERT(str != NULL);

  printf("checking wheter string size is initialized correctly");
  MCASSERT(str->size == 13);

  printf("checking wheter string data is initialized correctly");
  MCASSERT(strncmp(str->data, "initial value", 13) == 0);
  free_string(str);

  printf("checking wheter reference counter counts instanciated string");
  printf(" refcount = %i", str->refcount);
  MCASSERT(str->refcount == 1);

  printf("checking wheter reference counter counts instanciated string with same data");
  mcstring *new_str = new_string("initial value");
  MCASSERT(str->refcount == 2);

  printf("checking wheter pointer from new_string is the same as when previously called");
  MCASSERT(str == new_str);

  MCASSERT_SUMMARY;

  return MCASSERT_RETURN_STATUS;
}
