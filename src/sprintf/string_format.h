#pragma once
#ifndef string_format
#define string_format

#define spec_c 1
#define spec_d 2
#define spec_i 4
#define spec_e 8
#define spec_E 16
#define spec_f 32
#define spec_g 64
#define spec_G 128
#define spec_o 256
#define spec_s 512
#define spec_u 1024
#define spec_x 2048
#define spec_X 4096
#define spec_p 8192
#define spec_n 16384
#define spec_percent 32768

#define flag_minus 1
#define flag_plus 2
#define flag_space 4
#define flag_sharp 8
#define flag_0 16

#define len_h 1
#define len_l 2
#define len_L 4

typedef struct string_format {
  int specifier;
  int flags;
  int width;
  int precision;
  int len;
} FORMAT;

#endif