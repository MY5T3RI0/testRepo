#include <stdio.h>

#include "../sprintf/s21_sptintf.h"

int main() {
  char str[BUFFER_SIZE];
  char format[] = "%+011.15hd";

  sprintf(str, format, 5);
  printf("%s\n", str);
}