#include "reference.h"
#include <stdio.h>

static mcstring **references = NULL;
static size_t num_references = 0;

int mcstring_reference_offset(mcstring *reference) {
  int offset = -1;
  int x;
  for(x = 0; x < num_references; x++) {
    if(references[x] == reference) {
      offset = x;
      break;
    }
  }
  return offset;
}

unsigned char mcstring_reference_exists(mcstring *reference) {
  return mcstring_reference_offset(reference) >= 0;
}

mcstring *mcstring_add_reference(mcstring *reference) {
  mcstring *allocated_space = malloc(sizeof(mcstring) * 1);
  references = realloc(references, sizeof(mcstring*) * ++num_references);
  memcpy(allocated_space, reference, sizeof(mcstring));
  references[num_references - 1] = allocated_space;
  return allocated_space;
}

void mcstring_remove_reference(mcstring *reference) {
  int offset = mcstring_reference_offset(reference);
  if(offset >= 0) {
    free(references[offset]);
    memmove(&references[offset], &references[offset + 1], num_references - offset - 1);
    references = realloc(references, --num_references);
  }
}

mcstring *mcstring_reference_by_data(const char *data, size_t size) {
  mcstring *found = NULL;
  int x;
  for(x = 0; x < num_references; x++) {
    if(references[x]->size == size
      && strncmp(references[x]->data, data, size) == 0) {
      found = references[x];
    }
  }
  return found;
}
