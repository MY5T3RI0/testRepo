#include "s21_string.h"
char *s21_strchr(const char *str, int c) {
  void *chr = NULL;

  for (size_t i = 0; str[i] && !chr; i++)
    if (*(str + i) == c) chr = (char *)str + i;

  return chr;
}
