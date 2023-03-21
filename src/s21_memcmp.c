#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int ammount = 0;
  unsigned char *ustr1 = (unsigned char *)str1;
  unsigned char *ustr2 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (ustr1[i] != ustr2[i]) {
      ammount = ustr1[i] - ustr2[i];
      i = n;
    }
  }
  return ammount;
}