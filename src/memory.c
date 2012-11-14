#include "memory.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void mcstring_alloc(mcstring *object, size_t size) {
  if(size == 0) {
    mcstring_free(object);
  } else {
    if(object->data == NULL) {
      object->data = (char *)realloc(object->data, sizeof(mcchar) * size);
      assert(object->data != NULL);

      // if new size is larger initialize newly allocated uninitalized memory
      if(object->size < size) {
        memset(object->data + object->size, 0, sizeof(mcchar) * (size - object->size));
      }

      object->size = size;
    }
  }
}

void mcstring_free(mcstring *object) {
  free(object->data);
  object->size = 0;
}
