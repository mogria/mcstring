#ifndef MCstring_it_H
#define MCstring_it_H

#include "mcstring.h"

struct iterator;

struct string_it;

typedef struct string_it string_it;

typedef struct iterator iterator;

string_it *string_iterator(mcstring *string);
void free_iterator(iterator *it);
unsigned char iterator_move(iterator *it, int by, ...);
unsigned char iterator_next(iterator *it);
unsigned char iterator_prev(iterator *it);
void *iterator_get(iterator *it);
unsigned char valid_iterator(string_it *it);

#endif /* MCstring_it_H */
