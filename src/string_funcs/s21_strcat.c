#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  size_t start = s21_strlen(dest);
  size_t end = s21_strlen(src);
  for (size_t i = 0; i < end; i++) {
    dest[start + i] = src[i];
  }
  dest[start + end] = '\0';
  return dest;
}