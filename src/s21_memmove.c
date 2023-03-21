#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *udest = (unsigned char *)dest;
  unsigned char *usrc = (unsigned char *)src;
  unsigned char *temp = s21_NULL;

  if (dest != s21_NULL) {
    temp = (unsigned char *)calloc(n, sizeof(char));
    if (temp) {
      for (s21_size_t i = 0; i < n; i++) {
        temp[i] = usrc[i];
      }
      for (s21_size_t i = 0; i < n; i++) {
        udest[i] = temp[i];
      }
      free(temp);
    }
  }
  return dest;
}