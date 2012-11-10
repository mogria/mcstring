#include <mcstring/mcstring.h>
#include "memory.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

const mcstring *new_string(const char *data) {
  mcstring *string = calloc(1, sizeof(mcstring));
  assert(string != NULL);
  mcstring_alloc(string, strlen(data));
  mc_strncpy(string->data, data, string->size);
  string->data[string->size] = '\0';
  return string;
}

void free_string(mcstring *string) {
  mcstring_free(string);
  free(string);
}
