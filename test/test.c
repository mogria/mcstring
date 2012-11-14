#include <mcstring/mcstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "mcassert.h"

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
