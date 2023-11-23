#include "s21_string.h"
size_t s21_strcspn(const char *str1, const char *str2) {
  size_t res = 0;
  int is_searched = 0;

  for (size_t i = 0; i < s21_strlen(str1) && !is_searched; i++)
    if (s21_strchr(str2, str1[i])) {
      res = i;
      is_searched = 1;
    }

  return res;
}