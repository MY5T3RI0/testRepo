#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, size_t n) {
  unsigned char *destination = dest;
  const unsigned char *source = src;
  if (dest < src)
    for (size_t i = 0; i < n; i++) destination[i] = *(source + i);
  else
    for (size_t i = 0; i < n; i++)
      destination[n - i - 1] = *(source + n - i - 1);

  return dest;
}