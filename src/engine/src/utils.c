#include "utils.h"
#include <stdlib.h>
#include <string.h>

static char separator[] = PATH_SEPARATOR;

void append(PathBuilder *builder, const char *str) {
  size_t len = strlen(str);
  size_t sep_len = strlen(separator);
  if (builder->buffer == NULL) {
    builder->buffer = malloc(len + 1);
    builder->size = 0;
  }

  // don't append separator if the buffer is empty
  if (builder->size == 0) {
    builder->buffer = realloc(builder->buffer, len + 1);
    memcpy(builder->buffer + builder->size, str, len);
    builder->size += len;
    builder->buffer[builder->size] = '\0';
    return;
  }

  //append the separator
  if (builder->buffer != NULL) {
    builder->buffer = realloc(builder->buffer, builder->size + sep_len + len + 1);
    memcpy(builder->buffer + builder->size, separator, sep_len);
    builder->size += sep_len;
  } else {
    builder->buffer = malloc(len + 1);
  }
  //append the string
  memcpy(builder->buffer + builder->size, str, len);
  builder->size += len;
  builder->buffer[builder->size] = '\0';
}

void clear(PathBuilder *builder) {
  free(builder->buffer);
  builder->size = 0;
  builder->buffer = NULL;
}
