#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
  const unsigned char *result = str;
  void *chr = NULL;
  for (size_t i = 0; i < n && !chr; i++)
    if (*(result + i) == c) chr = (void *)(result + i);

  return chr;
}