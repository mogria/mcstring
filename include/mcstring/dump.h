#ifndef MCSTRING_DUMP_H
#define MCSTRING_DUMP_H

#include "mcstring.h"

char *string_hexdump(mcstring *string);
void file_hexdump(FILE *file, mcstring *string);
void print_hexdump(mcstring *string);

#endif /* MCSTRING_DUMP_H */
