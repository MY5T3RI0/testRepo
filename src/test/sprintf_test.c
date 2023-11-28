#include <stdio.h>

#include "../sprintf/s21_sptintf.h"

int main() {
  char str[BUFFER_SIZE];
  char format[] =
      "radix: %#x\n radiX: %#X\n octal: %#o\n char: %c\n int: %+4i\n decimal: "
      "%d\n "
      "string: "
      "%s\n "
      "unsigned: %u\n pointer: %p\n percent %%\n float: %#.4f";

  sprintf(str, format, 14, 13, 25, 'a', 36, -74, "str", -5, format, 5.);
  printf("%s\n", str);
}