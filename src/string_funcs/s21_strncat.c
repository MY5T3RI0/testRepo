#include "s21_string.h"
char *s21_strncat(char *dest, const char *src, size_t n) {
  size_t start = s21_strlen(dest);
  size_t end = start + s21_strlen(src) + 1;
  size_t len = end < n ? end : n;
  size_t size = start + len;

  for (size_t i = 0; i < len; i++) dest[start + i] = src[i];
  if (s21_strlen(dest) > size) dest[size] = '\0';
  return dest;
}