#include "s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
  size_t haystack_len = s21_strlen(haystack);
  size_t needle_len = s21_strlen(needle);
  char *current = (char *)haystack;
  char *temp = NULL;
  int is_searched = 0;

  if (!s21_strcmp(needle, "")) is_searched = 1;

  for (size_t i = 0; i < haystack_len && !is_searched && current; i++) {
    temp = s21_strchr(current, needle[0]);
    if (current == temp)
      current++;
    else
      current = temp;
    if (current) is_searched = !s21_strncmp(current, needle, needle_len);
  }

  return is_searched ? current : NULL;
}