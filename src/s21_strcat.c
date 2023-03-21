#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  s21_size_t x = s21_strlen(dest);
  for (s21_size_t i = 0; i < s21_strlen(src); i++) {
    dest[i + x] = src[i];
  }
  return dest;
}