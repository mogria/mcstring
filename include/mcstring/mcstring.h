#ifndef MCSTRING_MCSTRING_H
#define MCSTRING_MCSTRING_H

#include <stddef.h>

#define mc_strncpy(dest, src, size) strncpy((char *)(dest), (const char *)(src), (size))

typedef char mcchar;

typedef struct {
  size_t size;
  unsigned int refcount;
  mcchar *data;
} mcstring;

mcstring *new_string(const char *data);
mcstring *wrap_string(const char *data);
mcstring *new_sub_string(const char *data, size_t size, unsigned char copy);
const mcchar *string_data(mcstring *string);
size_t string_size(mcstring *string);
mcchar *c_string(mcstring *string);
void copy_string(char *dest, mcstring *src, size_t destsize);
mcstring *sub_string(mcstring *string, size_t offset, size_t size);
void free_string(mcstring *string);

#endif /* MCSTRING_MCSTRING_H  */
