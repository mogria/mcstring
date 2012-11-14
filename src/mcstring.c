#include <mcstring/mcstring.h>
#include "memory.h"
#include "reference.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

mcstring *new_string(const char *data) {
  mcstring *existed;
  mcstring *string = calloc(1, sizeof(mcstring));
  assert(string != NULL);

  string->size = strlen(data);

  if((existed = mcstring_reference_by_data(data, string->size)) != NULL) {
    free(string);
    string = existed;
  } else {
    mcstring_alloc(string, string->size);
    mc_strncpy(string->data, data, string->size);
    existed = string;
    string = mcstring_add_reference(string);
    free(existed);
  }
  string->refcount++;
  return string;
}

void free_string(mcstring *string) {
  if(!--string->refcount) {
    mcstring_free(string);
    mcstring_remove_reference(string);
  }
}
