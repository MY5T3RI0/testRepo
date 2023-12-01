#include "s21_string.h"

int s21_memcmp(const void* str1, const void* str2, size_t n) {
  const unsigned char* str_1 = str1;
  const unsigned char* str_2 = str2;
  int res = 0;

  for (size_t i = 0; i < n && !res; i++)
    if (*(str_1 + i) != *(str_2 + i)) res = *(str_1 + i) - *(str_2 + i);

  return res;
}