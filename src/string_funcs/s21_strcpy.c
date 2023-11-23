#include "s21_string.h"
char *s21_strcpy(char *dest, const char *src) {
  size_t len =
      s21_strlen(src) > s21_strlen(dest) ? s21_strlen(src) : s21_strlen(dest);

  for (size_t i = 0; i < len; i++) dest[i] = *(src + i);
  dest[len] = '\0';

  return dest;
}
