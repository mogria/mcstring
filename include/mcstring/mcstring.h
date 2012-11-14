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
void free_string(mcstring *string);

#endif /* MCSTRING_MCSTRING_H  */
