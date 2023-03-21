#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t x = s21_strlen(dest);
  s21_size_t i = 0;
  for (; i < n; i++) {
    dest[i + x] = src[i];
  }
  dest[i + x] = '\0';
  return dest;
}