#ifndef MCASSERT_H
#define MCASSERT_H

// maximum length of an error message
#define MCASSERT_MAX_ERROR_LENGTH 255

// initialize the testing system
#define MCASSERT_INIT \
  char **_mc_assert_errorbuffer = NULL; \
  unsigned int _mc_assert_num_ok = 0; \
  unsigned int _mc_assert_num_fail = 0

// make an assertion
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

// print summary of all failed tests (if there where one)
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

// 0 if no tests failed else 1
#define MCASSERT_RETURN_STATUS _mc_assert_num_fail > 0 ? EXIT_FAILURE : EXIT_SUCCESS;

#endif /* MCASSERT_H */
