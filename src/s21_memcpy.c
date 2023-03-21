#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *udest = (unsigned char *)dest;
  unsigned char *usrc = (unsigned char *)src;
  if (dest != s21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      udest[i] = usrc[i];
    }
  }
  return dest;
}