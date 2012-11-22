#ifndef MCSTRING_MCSTRING_H
#define MCSTRING_MCSTRING_H

#include <stddef.h>
#include <stdio.h>

#define mc_strncpy(dest, src, size) strncpy((char *)(dest), (const char *)(src), (size))

typedef char mcchar;

struct mcstring;

typedef struct mcstring mcstring;
 
// initializer
mcstring *new_string(const char *data);
mcstring *wrap_string(const char *data);
mcstring *new_sub_string(const char *data, size_t size, unsigned char copy);

// string internals
const mcchar *string_data(mcstring *string);
size_t string_size(mcstring *string);

// copy strings
mcchar *c_string(mcstring *string);
void copy_string(char *dest, mcstring *src, size_t destsize);

// sub string functions
mcstring *sub_string(mcstring *string, size_t offset, size_t size);
mcchar char_string(mcstring *string, int pos);

// manipulation
mcstring *reverse_string(mcstring *string);
mcstring *ltrim_string(mcstring *string, const char *chars);
mcstring *rtrim_string(mcstring *string, const char *chars);
mcstring *trim_string(mcstring *string, const char *chars);

// output functions
void write_string(FILE *file, mcstring *string);
void print_string(mcstring *string);

// free memory
void free_string(mcstring *string);

#endif /* MCSTRING_MCSTRING_H  */
