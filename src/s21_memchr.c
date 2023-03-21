#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *buffer = (unsigned char *)str;
  s21_size_t i = 0;
  unsigned char *ret_val = s21_NULL;
  while (i < n && buffer) {
    if ((*buffer) == (unsigned char)c) {
      ret_val = buffer;
      i = n;
    }
    buffer++;
    i++;
  }
  return ret_val;
}