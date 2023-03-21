#include "s21_string.h"

char *s21_strstr(const char *str, const char *needle) {
  const char *istr;
  char *str1;
  int flag = 0;
  if (s21_strlen(needle) > s21_strlen(str)) {
    istr = s21_NULL;
  } else {
    if (needle[0] == '\0') {
      istr = str;
    } else {
      istr = s21_NULL;
      int i = 0;
      str1 = (char *)str;
      while (str1[i] != '\0') {
        int k = 0, a = i;
        while (str1[a] == needle[k] && (str1[a] != '\0')) {
          a++;
          k++;
        }
        if (needle[k] == '\0' && flag == 0) {
          istr = &str1[i];
          flag = 1;
        }
        i++;
      }
    }
  }
  return ((char *)istr);
}