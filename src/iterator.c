#include <mcstring/iterator.h>
#include "type.h"
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#define CREATE_ITERATOR_STRUCT(name, type, contains) \
struct name { \
  type *iterable; \
  size_t pos; \
  unsigned char valid; \
  unsigned char (*move)(struct name *, int by); \
  void *(*get)(struct name *); \
};

CREATE_ITERATOR_STRUCT(iterator, void, void*)
CREATE_ITERATOR_STRUCT(string_it, mcstring, mcchar)

static unsigned char move_iterator(iterator *it, int by, size_t subject_size) {
  it->pos += by;
  return it->valid = (it->pos < subject_size ? 1 : 0);
}

static iterator *base_iterator(void *subject) {
  iterator *it = calloc(1, sizeof(iterator));
  it->iterable = subject;
  iterator_rewind(it);
  return it;
}

static unsigned char string_mover(string_it *it, int by) {
  return move_iterator((iterator *)it, by, ((mcstring*)it->iterable)->size);
}

static void *string_getter(string_it *it) {
  static mcchar return_value;
  if(it->valid) {
    return_value = it->iterable->data[it->pos];
    return (void *)&return_value;
  } else {
    return NULL;
  }
}

string_it *string_iterator(mcstring *string) {
  string_it *it = (string_it *)base_iterator(string);
  assert(it != NULL);
  it->move = string_mover;
  it->get = string_getter;
  return it;
}

void free_iterator(iterator *it) {
  if(it != NULL) {
    it->valid = 0;
    //it->get(it);
  }
  free((void*)it);
}

unsigned char iterator_move(iterator *iterator, int by, ...) {
  if(by == 0) {
    va_list arguments;
    va_start(arguments, by);
    iterator->move = va_arg(arguments, unsigned char (*)(struct iterator*, int by));
    va_end(arguments);
    return 1;
  } else {
    return iterator->move(iterator, by);
  }
}

void iterator_rewind(iterator *iterator) {
  iterator->pos = 0;
  iterator->valid = 1;
}

unsigned char iterator_next(iterator *iterator) {
  return iterator->move(iterator, 1);
}

unsigned char iterator_prev(iterator *iterator) {
  return iterator->move(iterator, -1);
}

void *iterator_get(iterator *it) {
  return it->get(it);
}

unsigned char valid_iterator(string_it *it) {
  return it->valid;
}
