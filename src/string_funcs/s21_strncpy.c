#include "s21_string.h"
char *s21_strncpy(char *dest, const char *src, size_t n) {
  size_t end =
      s21_strlen(src) > s21_strlen(dest) ? s21_strlen(src) : s21_strlen(dest);
  size_t len = end < n ? end : n;

  for (size_t i = 0; i < len; i++) dest[i] = *(src + i);
  dest[end] = '\0';

  return dest;
}
