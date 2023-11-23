#include "s21_string.h"
#include "stdio.h"  //TODO: remove header

char *s21_strerror(int errnum) {
  static char error[STRERR_MAX];
  ARRAY;

  if (errnum > ERR_MAX) {
    char buff[4096];
    sprintf(buff, "%s%d", ERROR, errnum);  // TODO: change to own sprintf
    s21_strcpy(error, buff);
  } else
    s21_strcpy(error, errlist[errnum]);

  return error;
}