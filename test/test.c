#include <mcstring/mcstring.h>
#include "../src/type.h"
#include <mcstring/dump.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "mcassert.h"

int main(int argc, char **argv) {
  MCASSERT_INIT;

  // --------------------------------------------------------------------- //
  // initialization & memory managment                                     //
  // --------------------------------------------------------------------- //
  printf("checking wheter string initializes correctly");
  mcstring *str = new_string("initial value");
  MCASSERT(str != NULL);

  printf("checking wheter string size is initialized correctly");
  MCASSERT(str->size == 13);

  printf("checking wheter reference counter counts instanciated string");
  MCASSERT(str->refcount == 1);

  printf("checking wheter string data is initialized correctly");
  MCASSERT(strncmp(str->data, "initial value", 13) == 0);
  free_string(str);

  // --------------------------------------------------------------------- //
  // reference counting                                                    //
  // --------------------------------------------------------------------- //
  printf("checking refcount after freeing string ");
  MCASSERT(str->refcount == 0);

  printf("checking wheter reference counter counts instanciated string with same data");
  str = new_string("initial value");
  mcstring *new_str = new_string("initial value");
  MCASSERT(str->refcount == 2);

  printf("checking wheter reference counter is correct with string containing other data");
  mcstring *diffrent_str = new_string("another value");
  MCASSERT(diffrent_str->refcount == 1);

  // --------------------------------------------------------------------- //
  // check if strings with same data point to same location                //
  // --------------------------------------------------------------------- //
  printf("checking wheter pointer from new_string is the same as when previously called");
  MCASSERT(str == new_str);

  printf("checking wheter pointer from new_string is an other when called with diffrent data");
  MCASSERT(diffrent_str != new_str);

  // --------------------------------------------------------------------- //
  // output checks of hexdump                                              //
  // --------------------------------------------------------------------- //
  printf("checking wheter hexdumping string works correctly");
  char *dump;
  MCASSERT(strcmp(dump = string_hexdump(new_str), "69 6E 69 74 69 61 6C 20 76 61 6C 75 65") == 0);
  free(dump);

  free_string(new_str);
  free_string(str);

  MCASSERT_SUMMARY;

  return MCASSERT_RETURN_STATUS;
}
