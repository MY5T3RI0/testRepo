#include "s21_string.h"
size_t s21_strspn(const char *str1, const char *str2) {
  size_t res = 0;

  while (s21_strchr(str2, str1[res])) res++;

  return res;
}