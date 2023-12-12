#include <stdio.h>

#include "../s21_string.h"

int main() {
  char str1[BUFFER_SIZE];
  char str2[BUFFER_SIZE];

  double d = -0.004567;
  long double lf1 = 123.567L;
  int res1 = s21_sprintf(str1, "%.0g %#20.g %+#.Lg", d, d, d, lf1);
  int res2 = sprintf(str2, "%.0g %#20.g %+#.Lg", d, d, lf1);

  printf("%s\n", str1);
  printf("res = %d\n", res1);
  printf("-------------------\n");
  printf("%s\n", str2);
  printf("res = %d\n", res2);
}