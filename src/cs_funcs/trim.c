#include "../string_funcs/s21_string.h"
#include "cs_string.h"

void *trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) return NULL;

  size_t start = 0;
  size_t end = s21_strlen(src) + 1;

  if (s21_strchr(trim_chars, src[start]))
    while (s21_strchr(trim_chars, src[++start]))
      ;
  while (s21_strchr(trim_chars, src[--end - 1]))
    ;

  size_t len = end - start;
  char *new_str = malloc((len + 1) * sizeof(char));

  if (new_str) {
    for (int i = start, j = 0; i < end; i++, j++) new_str[j] = src[i];
    new_str[len] = '\0';
  }

  return new_str;
}