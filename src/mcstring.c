#include <mcstring/mcstring.h>
#include "memory.h"
#include "reference.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

mcstring *new_string(const char *data) {
  return new_sub_string(data, strlen(data), 1);
}

mcstring *wrap_string(const char *data) {
  return new_sub_string(data, strlen(data), 0);
}

mcstring *new_sub_string(const char *data, size_t size, unsigned char copy) {
  mcstring *existed;
  mcstring *string = calloc(1, sizeof(mcstring));
  assert(string != NULL);

  string->size = size;

  if((existed = mcstring_reference_by_data(data, string->size)) != NULL) {
    free(string);
    string = existed;
  } else {
    if(copy) {
      mcstring_alloc(string, string->size);
      mc_strncpy(string->data, data, string->size);
    } else {
      string->data = data;
    }
    existed = string;
    string = mcstring_add_reference(string);
    free(existed);
  }
  string->refcount++;
  return string;
}

// not null terminated
const mcchar *string_data(mcstring *string) {
  return string->data;
}

size_t string_size(mcstring *string) {
  return string->size;
}

// null terminated, returned string needs to be free()'d
mcchar *c_string(mcstring *string) {
  mcchar *buffer = malloc((string->size + 1) * sizeof(mcchar));
  mc_strncpy(buffer, string->data, string->size);
  buffer[string->size] = '\0';
  return buffer;
}


void copy_string(char *dest, mcstring *src, size_t destsize) {
  mc_strncpy(dest, src->data, destsize);
  dest[destsize - 1] = '\0';
}

mcstring *sub_string(mcstring *string, size_t offset, size_t size) {
  size_t max_size;
  if(offset > string->size) {
    offset = string->size;
  }

  max_size = string->size - offset;

  if(size > max_size) {
    size = max_size;
  }
  
  return new_sub_string(string->data + offset, size, 0);
}

void free_string(mcstring *string) {
  if(!--string->refcount) {
    mcstring_free(string);
    mcstring_remove_reference(string);
  }
}
