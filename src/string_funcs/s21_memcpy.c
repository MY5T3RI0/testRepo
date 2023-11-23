#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, size_t n) {
  unsigned char *destination = dest;
  const unsigned char *source = src;
  size_t len = s21_strlen(src) < n ? s21_strlen(src) + 1 : n;
  for (size_t i = 0; i < len; i++) {
    destination[i] = *(source + i);
  }

  return dest;
}
