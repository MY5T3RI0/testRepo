#include <stdio.h>

#include "../sprintf/s21_sptintf.h"

int main() {
  char str[BUFFER_SIZE];
  char format[] =
      "radix: %#x\n radiX: %#X\n octal: %#o\n char: %c\n int: %+4i\n "
      "decimal: "
      "%d\n "
      "string: "
      "%s\n "
      "unsigned: %u\n pointer: %p\n percent %%\n float: %#.4f\n scientific: "
      "%.4e\n upper scientific: %.2E\n spec_g: %.0g";

  sprintf(str, format, 14, 13, 25, 'a', 36, -74, "str", -5, format, 1.00004,
          100.004, 0.036, 1000.00005);
  printf("%s\n", str);
}