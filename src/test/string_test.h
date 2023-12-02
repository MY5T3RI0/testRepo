#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../common/file.h"
#include "../s21_string.h"

#define LINE "------------------------\n"
#define RECIEVED_PATH "recieved.txt"
#define EXPECTED_PATH "expected.txt"
#define FUNC_NUM atoi(argv[1])
#define STR1 argv[2]
#define STR2 argv[3]
#define SIZE (size_t) atoi(argv[4])
#define SYM atoi(argv[5])
#define STR3 argv[6]
#define STR4 argv[7]

void strchr_test(char *(*strchr_func)(const char *str, int c), const char *str1,
                 int c, const char *path);
void strcmp_test(int (*strcmp_func)(const char *str1, const char *str2),
                 const char *str1, const char *str2, const char *path);
void strncat_test(char *(*strncat_func)(char *dest, const char *src, size_t n),
                  char *str1, const char *str2, size_t n, const char *path);
void strcat_test(char *(*strcat_func)(char *dest, const char *src), char *str1,
                 const char *str2, const char *path);
void memset_test(void *(*memset_func)(void *str, int c, size_t n), char *str1,
                 int c, size_t n, const char *path);
void memcpy_test(void *(*memcpy_func)(void *dest, const void *src, size_t n),
                 char *str1, const char *str2, size_t len, const char *path);
void memchr_test(void *(*memchr_func)(const void *str, int c, size_t n),
                 const char *str, int c, size_t n, const char *path);
void memcmp_test(int (*memcmp_func)(const void *str1, const void *str2,
                                    size_t n),
                 const char *str1, const char *str2, size_t n,
                 const char *path);
void memmove_test(void *(*memmove_func)(void *str1, const void *src2, size_t n),
                  char *str1, const char *str2, size_t n, const char *path);
void strtok_test(char *(*strtok_func)(char *str1, const char *str2), char *str1,
                 const char *str2, const char *path);
void strstr_test(char *(*strstr_func)(const char *str1, const char *str2),
                 const char *str1, const char *str2, const char *path);
void strspn_test(size_t (*strspn_func)(const char *str1, const char *str2),
                 const char *str1, const char *str2, const char *path);
void strrchr_test(char *(*strrchr_func)(const char *str1, int c),
                  const char *str1, int c, const char *path);
void strpbrk_test(char *(*strpbrk_func)(const char *str1, const char *str2),
                  const char *str1, const char *str2, const char *path);
void strlen_test(size_t (*strlen_func)(const char *str1), const char *str1,
                 const char *path);
void strerror_test(char *(*strerror_func)(int errnum), int errnum,
                   const char *path);
void strerror_test(char *(*strerror_func)(int errnum), int errnum,
                   const char *path);
void strcspn_test(size_t (*strcspn_func)(const char *str1, const char *str2),
                  const char *str1, const char *str2, const char *path);
void strncpy_test(char *(strncpy_func)(char *dest, const char *src, size_t n),
                  char *str1, const char *str2, size_t n, const char *path);
void strcpy_test(char *(strcpy_func)(char *dest, const char *src), char *str1,
                 const char *str2, const char *path);
void strncmp_test(int (*strncmp_func)(const char *str1, const char *str2,
                                      size_t n),
                  const char *str1, const char *str2, size_t n,
                  const char *path);

void print_file(const char *str, const char *path);
void print_func_res_even(int c, char *argv[]);
void print_func_res_odd(int c, char *argv[]);