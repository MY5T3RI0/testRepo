#include <stdio.h>

#include "../s21_string.h"

int main() {
  char str1[BUFFER_SIZE];
  char str2[BUFFER_SIZE];
  //   char format[] =
  //       "radix: %#x\n radiX: %#X\n octal: %#o\n char: %c\n int: %+4i\n "
  //       "decimal: "
  //       "%d\n "
  //       "string: "
  //       "%s\n "
  //       "unsigned: %u\n pointer: %p\n percent %%\n float: %#+20.4f\n
  //       scientific: "
  //       "%e\n upper scientific: %.2E\n spec_g: %#G";

  //   int res1 = s21_sprintf(str1, format, 14, 13, 25, 'a', 36, -74, "str", -5,
  //                          format, 1.00004, 123.4567890, 0.036,
  //                          1234567.4567890);
  //   int res2 = sprintf(str2, format, 14, 13, 25, 'a', 36, -74, "str", -5,
  //   format,
  //                      1.00004, 123.4567890, 0.036, 1234567.4567890);

  char format[] = "%s %g %ls";
  char *hello = "Hello";
  wchar_t *wchar = L"some words";
  int res1 = s21_sprintf(str1, format, hello, 123456.456, wchar);
  int res2 = sprintf(str2, format, hello, 123456.456, wchar);

  printf("%s\n", str1);
  printf("res = %d\n", res1);
  printf("-------------------\n");
  printf("%s\n", str2);
  printf("res = %d\n", res2);
}