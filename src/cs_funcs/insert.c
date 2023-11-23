#include "../string_funcs/s21_string.h"
#include "cs_string.h"

void *insert(const char *src, const char *str, size_t start_index) {
  if (!src || s21_strlen(src) < start_index || !str) return NULL;

  char *new_str = malloc((s21_strlen(src) + 1) * sizeof(char));

  if (new_str) {
    s21_strcpy(new_str, src);
    s21_strcpy((char *)new_str + start_index, str);
    new_str[s21_strlen(new_str)] = '\0';
  }

  return new_str;
}