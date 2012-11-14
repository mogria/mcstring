#ifndef MCSTRING_REFERENCE_H
#define MCSTRING_REFERENCE_H

#include <mcstring/mcstring.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

unsigned char mcstring_reference_exists(mcstring *reference);
mcstring *mcstring_add_reference(mcstring *reference);
void mcstring_remove_reference(mcstring *reference);
mcstring *mcstring_reference_by_data(const char *data, size_t size);

#endif /* MCSTRING_REFERENCE_H */

