#include "s21_string.h"
int s21_strncmp(const char *str1, const char *str2, size_t n) {
  size_t end =
      s21_strlen(str1) > s21_strlen(str2) ? s21_strlen(str1) : s21_strlen(str2);
  size_t len = end < n ? end : n;
  int res = 0;

  for (size_t i = 0; i < len && !res; i++)
    if (*(str1 + i) != *(str2 + i)) res = *(str1 + i) - *(str2 + i);

  return res > 0 ? 1 : res < 0 ? -1 : 0;
}