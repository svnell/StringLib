#include "s21_strerror.h"

#include "s21_string.h"

char *s21_strerror(int errnum) {
  static char err[100];

  if (errnum < 0 || errnum >= S21_ERRLIST_SIZE) {
#if defined(__APPLE__)
    s21_sprintf(err, "Unknown error: %d", errnum);  // заменить на s21_sprintf
#endif
#if defined(__linux__)
    s21_sprintf(err, "Unknown error %d", errnum);  // заменить на s21_sprintf
#endif
  } else {
    s21_strcpy(err, s21_sys_errlist[errnum]);
  }

  return err;
}