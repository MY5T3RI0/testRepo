#include "string_test.h"

int main(int argc, char *argv[]) {
  if (argc < 2)
    printf("func not defined\n");
  else if (FUNC_NUM % 2 == 0)
    print_func_res_even(FUNC_NUM, argv);
  else if (FUNC_NUM % 2 == 1)
    print_func_res_odd(FUNC_NUM, argv);
}

void print_func_res_even(int c, char *argv[]) {
  switch (c) {
    case 2:
      memcmp_test(memcmp, STR1, STR2, SIZE, EXPECTED_PATH);
      memcmp_test(s21_memcmp, STR3, STR4, SIZE, RECIEVED_PATH);
      break;
    case 4:
      memmove_test(memmove, STR1, STR2, SIZE, EXPECTED_PATH);
      memmove_test(s21_memmove, STR3, STR4, SIZE, RECIEVED_PATH);
      break;
    case 6:
      strcat_test(strcat, STR1, STR2, EXPECTED_PATH);
      strcat_test(s21_strcat, STR3, STR4, RECIEVED_PATH);
      break;
    case 8:
      strchr_test(strchr, STR1, SYM, EXPECTED_PATH);
      strchr_test(s21_strchr, STR3, SYM, RECIEVED_PATH);
      break;
    case 10:
      strncmp_test(strncmp, STR1, STR2, SIZE, EXPECTED_PATH);
      strncmp_test(s21_strncmp, STR3, STR4, SIZE, RECIEVED_PATH);
      break;
    case 12:
      strncpy_test(strncpy, STR1, STR2, SIZE, EXPECTED_PATH);
      strncpy_test(s21_strncpy, STR3, STR4, SIZE, RECIEVED_PATH);
      break;
    case 14:
      strerror_test(strerror, SYM, EXPECTED_PATH);
      strerror_test(s21_strerror, SYM, RECIEVED_PATH);
      break;
    case 16:
      strpbrk_test(strpbrk, STR1, STR2, EXPECTED_PATH);
      strpbrk_test(s21_strpbrk, STR3, STR4, RECIEVED_PATH);
      break;
    case 18:
      strspn_test(strspn, STR1, STR2, EXPECTED_PATH);
      strspn_test(s21_strspn, STR3, STR4, RECIEVED_PATH);
      break;
    case 20:
      strtok_test(strtok, STR1, STR2, EXPECTED_PATH);
      strtok_test(s21_strtok, STR3, STR4, RECIEVED_PATH);
      break;
    default:
      printf("invalid func num");
      break;
  }
}

void print_func_res_odd(int c, char *argv[]) {
  switch (c) {
    case 1:
      memchr_test(memchr, STR1, SYM, SIZE, EXPECTED_PATH);
      memchr_test(s21_memchr, STR3, SYM, SIZE, RECIEVED_PATH);
      break;
    case 3:
      memcpy_test(memcpy, STR1, STR2, SIZE, EXPECTED_PATH);
      memcpy_test(s21_memcpy, STR3, STR4, SIZE, RECIEVED_PATH);
      break;
    case 5:
      memset_test(memset, STR1, SYM, SIZE, EXPECTED_PATH);
      memset_test(s21_memset, STR3, SYM, SIZE, RECIEVED_PATH);
      break;
    case 7:
      strncat_test(strncat, STR1, STR2, SIZE, EXPECTED_PATH);
      strncat_test(s21_strncat, STR3, STR4, SIZE, RECIEVED_PATH);
      break;
    case 9:
      strcmp_test(strcmp, STR1, STR2, EXPECTED_PATH);
      strcmp_test(s21_strcmp, STR3, STR4, RECIEVED_PATH);
      break;
    case 11:
      strcpy_test(strcpy, STR1, STR2, EXPECTED_PATH);
      strcpy_test(s21_strcpy, STR3, STR4, RECIEVED_PATH);
      break;
    case 13:
      strcspn_test(strcspn, STR1, STR2, EXPECTED_PATH);
      strcspn_test(s21_strcspn, STR3, STR4, RECIEVED_PATH);
      break;
    case 15:
      strlen_test(strlen, STR1, EXPECTED_PATH);
      strlen_test(s21_strlen, STR3, RECIEVED_PATH);
      break;
    case 17:
      strrchr_test(strrchr, STR1, SYM, EXPECTED_PATH);
      strrchr_test(s21_strrchr, STR3, SYM, RECIEVED_PATH);
      break;
    case 19:
      strstr_test(strstr, STR1, STR2, EXPECTED_PATH);
      strstr_test(s21_strstr, STR3, STR4, RECIEVED_PATH);
      break;
    default:
      printf("invalid func num");
      break;
  }
}

void strcspn_test(size_t (*strcspn_func)(const char *str1, const char *str2),
                  const char *str1, const char *str2, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strcspn_test\n%lu\n", strcspn_func(str1, str2));
  print_file(str, path);
}

void strtok_test(char *(*strtok_func)(char *str1, const char *str2), char *str1,
                 const char *str2, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strtok_test\n%s\n", strtok_func(str1, str2));
  print_file(str, path);
}

void strstr_test(char *(*strstr_func)(const char *str1, const char *str2),
                 const char *str1, const char *str2, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strstr_test\n%s\n", strstr_func(str1, str2));
  print_file(str, path);
}

void strspn_test(size_t (*strspn_func)(const char *str1, const char *str2),
                 const char *str1, const char *str2, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strspn_test\n%lu\n", strspn_func(str1, str2));
  print_file(str, path);
}

void strrchr_test(char *(*strrchr_func)(const char *str1, int c),
                  const char *str1, int c, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strrchr_test\n%s\n", strrchr_func(str1, c));
  print_file(str, path);
}

void strpbrk_test(char *(*strpbrk_func)(const char *str1, const char *str2),
                  const char *str1, const char *str2, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strpbrk_test\n%s\n", strpbrk_func(str1, str2));
  print_file(str, path);
}

void strlen_test(size_t (*strlen_func)(const char *str1), const char *str1,
                 const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strlen_test\n%lu\n", strlen_func(str1));
  print_file(str, path);
}

void strerror_test(char *(*strerror_func)(int errnum), int errnum,
                   const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strerror_test\n%s\n", strerror_func(errnum));
  print_file(str, path);
}

void strcsp_test(size_t (*strcspn_func)(const char *str1, const char *str2),
                 const char *str1, const char *str2, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strcsp_test\n%lu\n", strcspn_func(str1, str2));
  print_file(str, path);
}

void strncpy_test(char *(strncpy_func)(char *dest, const char *src, size_t n),
                  char *str1, const char *str2, size_t n, const char *path) {
  char str[BUFFER_SIZE];
  char *new_str = strncpy_func(str1, str2, n);
  sprintf(str, "strncpy_test\n%s %s\n", str1, new_str);
  print_file(str, path);
}

void strcpy_test(char *(strcpy_func)(char *dest, const char *src), char *str1,
                 const char *str2, const char *path) {
  char str[BUFFER_SIZE];
  char *new_str = strcpy_func(str1, str2);
  sprintf(str, "strcmp_test\n%s %s\n", str1, new_str);
  print_file(str, path);
}

void strncmp_test(int (*strncmp_func)(const char *str1, const char *str2,
                                      size_t n),
                  const char *str1, const char *str2, size_t n,
                  const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strncmp_test\n%d\n", strncmp_func(str1, str2, n));
  print_file(str, path);
}

void strchr_test(char *(*strchr_func)(const char *str, int c), const char *str1,
                 int c, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strchr_test\n%s\n", strchr_func(str1, c));
  print_file(str, path);
}

void strcmp_test(int (*strcmp_func)(const char *str1, const char *str2),
                 const char *str1, const char *str2, const char *path) {
  char str[BUFFER_SIZE];
  sprintf(str, "strcmp_test\n%d\n", strcmp_func(str1, str2));
  print_file(str, path);
}

void strncat_test(char *(*strncat_func)(char *dest, const char *src, size_t n),
                  char *str1, const char *str2, size_t n, const char *path) {
  char *new_str = strncat_func(str1, str2, n);
  char str[BUFFER_SIZE];
  sprintf(str, "strncat_test\n%s %s\n", str1, new_str);
  print_file(str, path);
}

void strcat_test(char *(*strcat_func)(char *dest, const char *src), char *str1,
                 const char *str2, const char *path) {
  char *new_str = strcat_func(str1, str2);
  char str[BUFFER_SIZE];
  sprintf(str, "strcat_test\n%s %s\n", str1, new_str);
  print_file(str, path);
}

void memmove_test(void *(*memmove_func)(void *str1, const void *src2, size_t n),
                  char *str1, const char *str2, size_t n, const char *path) {
  char *new_str = memmove_func(str1, str2, n);
  char str[BUFFER_SIZE];
  sprintf(str, "memmove_test\n%s %s\n", str1, new_str);
  print_file(str, path);
}

void memset_test(void *(*memset_func)(void *str, int c, size_t n), char *str1,
                 int c, size_t n, const char *path) {
  char *str2 = memset_func(str1, c, n);
  char str[BUFFER_SIZE];
  sprintf(str, "memset_test\n%s %s\n", str1, str2);
  print_file(str, path);
}

void memcpy_test(void *(*memcpy_func)(void *dest, const void *src, size_t n),
                 char *str1, const char *str2, size_t len, const char *path) {
  char *new_str = memcpy_func(str1, str2, len);
  char str[BUFFER_SIZE];
  sprintf(str, "memcpy_test\n%s %s\n", (char *)str1, new_str);
  print_file(str, path);
}

void memchr_test(void *(*memchr_func)(const void *str, int c, size_t n),
                 const char *str1, int c, size_t n, const char *path) {
  char *sym = (char *)memchr_func(str1, c, n);
  char str[BUFFER_SIZE];
  sprintf(str, "memchr_test:\n%s\n", sym);
  print_file(str, path);
}

void memcmp_test(int (*memcmp_func)(const void *str1, const void *str2,
                                    size_t n),
                 const char *str1, const char *str2, size_t n,
                 const char *path) {
  int cmp = memcmp_func(str1, str2, n);
  char str[BUFFER_SIZE];
  sprintf(str, "memcmp test:\n%d\n", cmp);
  print_file(str, path);
}

void print_file(const char *str, const char *path) {
  FILE *file = file_init(path, "w");
  int state = file != NULL;
  if (state) {
    fputs(str, file);
    close_file(file);
  }
}