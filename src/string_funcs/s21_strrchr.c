#include "s21_string.h"
char *s21_strrchr(const char *str, int c) {
  void *chr = NULL;
  size_t len = s21_strlen(str);

  for (size_t i = 0; i < len && !chr; i++)
    if (*(str + len - i - 1) == c) chr = (char *)str + len - i - 1;

  return chr;
}
