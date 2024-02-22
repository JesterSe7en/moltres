#ifndef MOLTRES_SRC_UTILS_H_
#define MOLTRES_SRC_UTILS_H_

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#else
#include <limits.h>
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

typedef struct {
  char *buffer;
  size_t size;
} PathBuilder;

void append(PathBuilder *builder, const char *str);
void clear(PathBuilder *builder);
#endif //MOLTRES_SRC_UTILS_H_
