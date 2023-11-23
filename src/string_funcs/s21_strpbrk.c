#include "s21_string.h"
char *s21_strpbrk(const char *str1, const char *str2) {
  size_t i = 0;
  size_t len = s21_strlen(str1);

  for (char *res = s21_strchr(str2, str1[0]); i < len && !res;)
    res = s21_strchr(str2, str1[++i]);

  return i < len ? (char *)&str1[i] : NULL;
}