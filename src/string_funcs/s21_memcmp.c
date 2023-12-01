#include "s21_string.h"

int s21_memcmp(const void* str1, const void* str2, size_t n) {
  int compare_index = 0;
  for (size_t i = 0; i < n && compare_index == 0; i++) {
	compare_index = *((char*)str1 + i) - *((char*)str2 + i);
  }

  return compare_index;
}