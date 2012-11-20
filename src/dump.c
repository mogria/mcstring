#include <mcstring/dump.h>
#include "type.h"
#include <stdio.h>
#include <stdlib.h>

#define HEX_SEGMENT_SIZE (sizeof(mcchar) * 2)
#define SEGMENT_SIZE (HEX_SEGMENT_SIZE + 1)

static char *hexdump_format() {
  static char format[10] = {};
  if(format[0] == '\0') {
    snprintf(format, 10, "%%0%iX", HEX_SEGMENT_SIZE);
  }
  return format;
}

char *string_hexdump(mcstring *string) {
  char *ret = malloc(SEGMENT_SIZE * string->size);
  char *sprintf_format = hexdump_format();
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

void file_hexdump(FILE *file, mcstring *string) {
  char *printf_format = hexdump_format();
  int x;
  for(x = 0; x < string->size; x++) {
    fprintf(file, printf_format, string->data[x]);
    fprintf(file, " ");
  }
}

void print_hexdump(mcstring *string) {
  return file_hexdump(stdout, string);
}
