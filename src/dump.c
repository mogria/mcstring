#include <mcstring/dump.h>
#include <stdio.h>
#include <stdlib.h>

#define HEX_SEGMENT_SIZE (sizeof(mcchar) * 2)
#define SEGMENT_SIZE (HEX_SEGMENT_SIZE + 1)

const char *string_hexdump(mcstring *string) {
  char *ret = malloc(SEGMENT_SIZE * string->size);
  char sprintf_format[10];
  snprintf(sprintf_format, 10, "%%0%iX", HEX_SEGMENT_SIZE);
  int x;
  for(x = 0; x < string->size; x++) {
    snprintf(ret + x * SEGMENT_SIZE,
        SEGMENT_SIZE,
        sprintf_format,
        (unsigned int)(string->data[x]));
    ret[x * SEGMENT_SIZE + HEX_SEGMENT_SIZE] = ' ';
  }
  ret[x * SEGMENT_SIZE - 1] = '\0';

  return ret;
}
