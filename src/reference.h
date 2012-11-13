#ifndef MCSTRING_REFERENCE_H
#define MCSTRING_REFERENCE_H

#include <mcstring/mcstring.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

unsigned char mcstring_reference_exists(mcstring *reference);
mcstring *mcstring_add_reference(mcstring *reference);
unsigned char mcstring_data_exists(mcstring *reference);

#endif /* MCSTRING_REFERENCE_H */

