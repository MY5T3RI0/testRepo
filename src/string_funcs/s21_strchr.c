#include "s21_string.h"
char *s21_strchr(const char *str, int c) {
  void *chr = NULL;
  size_t len = s21_strlen(str);

  for (size_t i = 0; i < len && !chr; i++)
    if (*(str + i) == c) chr = (char *)str + i;

  return chr;
}
