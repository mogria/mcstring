#include "type.h"
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

    if(!copy)  {
      free(*(char**)&data);
    }
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

mcchar char_string(mcstring *string, int pos) {
  mcchar c = '\0';
  if(pos < 0) {
    pos = string->size + pos;
  }

  if(pos >= 0 && pos < string->size) {
    c = string->data[pos];
  }
  return c;
}

mcstring *reverse_string(mcstring *string) {
  int x;
  mcchar *buffer = c_string(string);
  mcchar tmp;
  for(x = 0; x < string->size / 2; x++) {
    tmp = buffer[x];
    buffer[x] = buffer[string->size - x - 1];
    buffer[string->size - x - 1] = tmp;
  }

  return wrap_string(buffer);
}

mcstring *ltrim_string(mcstring *string, const char *chars) {
  size_t x, y;
  unsigned char found = 1;
  size_t found_counter = 0;
  for(y = 0; y < string->size && found; y++) {
    mcchar c = string->data[y];
    for(x = 0; chars[x] != 0; x++) {
      if(c == chars[x]) {
        found_counter++;
      }
    }
  }
  return sub_string(string, found_counter, string->size - found_counter);
}

mcstring *rtrim_string(mcstring *string, const char *chars) {
  size_t x, y;
  unsigned char found = 1;
  size_t found_counter = 0;
  for(y = string->size; y > 0 && found; y--) {
    mcchar c = string->data[y];
    for(x = 0; chars[x] != 0; x++) {
      if(c == chars[x]) {
        found_counter++;
      }
    }
  }
  return sub_string(string, 0, string->size - found_counter);
}

mcstring *trim_string(mcstring *string, const char *chars) {
  return ltrim_string(rtrim_string(string, chars), chars);
}

void write_string(FILE *file, mcstring *string) {
  int size = string_size(string) + 1;
  mcchar data[size];
  copy_string(data, string, size);
  fprintf(file, "%s", data);
}

void print_string(mcstring *string) {
  write_string(stdout, string);
}

void free_string(mcstring *string) {
  if(!--string->refcount) {
    mcstring_free(string);
    mcstring_remove_reference(string);
  }
}
