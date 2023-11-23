#include "s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
  size_t haystack_len = s21_strlen(haystack);
  size_t needle_len = s21_strlen(needle);
  char *temp = (char *)haystack;
  int is_searched = 0;

  if (!s21_strcmp(needle, "")) is_searched = 1;

  for (size_t i = 0; i < haystack_len && !is_searched && temp; i++) {
    temp = s21_strchr(temp + i, needle[0]);
    if (temp) is_searched = !s21_strncmp(temp, needle, needle_len);
  }

  return is_searched ? temp : NULL;
}