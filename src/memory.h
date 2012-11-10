#ifndef MCSTRING_MEMORY_H
#define MCSTRING_MEMORY_H

#include <mcstring/mcstring.h>

void mcstring_alloc(mcstring *object, size_t size);
void mcstring_free(mcstring *object);

#endif /* MCSTRING_MEMORY_H  */
