#include "emerald.h"

char* readfile (char filename[], int *fileSize) {
  FILE *file = fopen(filename, "r");

  if (!file) {
    die("Could not open file: %s", filename);
  }

  fseek(file, 0L, SEEK_END);
  int size = ftell(file);
  *fileSize = size;
  fseek(file, 0L, SEEK_SET);

  char* buffer = malloc(sizeof(char*) * size);
  fread(buffer, size, 1, file);
  fclose(file);
  return buffer;
}


void die (const char * format, ...) {
  va_list vargs;
  va_start(vargs, format);
  vfprintf(stderr, format, vargs);
  fprintf(stderr, "\n");
  exit (1);
}

void debug (char *msg) {
  printf(" \e[36m%s\e[0m\n", msg);
}

