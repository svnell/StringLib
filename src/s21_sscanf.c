#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int non_empty_string = checkString(str);
  int success = 0;
  int convertions = 0;

  if (non_empty_string) {
    va_list var;
    va_start(var, format);
    const s21_size_t str_len = s21_strlen(str);
    char skip = '\0';
    while (*format != '\0') {
      if (*format == '%') {
        flags_t flag_format = {0};
        format++;
        parseFormat(&format, &flag_format);
        if (flag_format.error) break;
        parseString(&str, str_len, &flag_format, var, skip);
        if (flag_format.convertions) convertions++;
        success++;
        if (flag_format.error) break;
        skip = '\0';
      } else if (skip == '\0' || skip == *format) {
        skip = *format;
        format++;
      } else {
        break;
      }
    }
    va_end(var);
  }

  return success ? convertions : -1;
}

int checkString(const char *str) {
  int res = 0;

  for (int i = 0; str[i]; i++) {
    if (!isSeporator(str[i])) {
      res = 1;
      break;
    }
  }

  return res;
}

void parseFormat(const char **format, flags_t *f) {
  *format = parseWidth(*format, f);
  *format = parseLength(*format, f);
  *format = parseSpecifier(*format, f);
}

const char *parseWidth(const char *format, flags_t *f) {
  char tempWidth[512] = {'\0'};
  int i = 0;
  while (*format == '*' || (*format >= 48 && *format <= 57)) {
    if (*format == '*') {
      f->asterics = 1;
    } else if (!f->asterics) {
      tempWidth[i] = *format;
      i++;
    }
    format++;
  }
  if (i) f->width = s21_atoii(tempWidth);
  if (f->width == 0) f->width = -1;
  return format;
}

const char *parseLength(const char *format, flags_t *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
      if ((*format) == 'l') format++;
      break;
    case 'L':
      f->length = 'L';
      format++;
      break;
  }
  return format;
}

const char *parseSpecifier(const char *format, flags_t *f) {
  char specList[17] = "cdieEfgGosuxXpn%";
  int unmatch = 1;
  for (int i = 0; i < 16; i++) {
    if (*format == specList[i]) {
      f->specifier = specList[i];
      unmatch = 0;
      break;
    }
  }
  f->error = unmatch;

  return ++format;
}

void parseString(const char **str, const s21_size_t str_len, flags_t *f,
                 va_list var, char skip) {
  char str_temp[1024] = {'\0'};
  char ch = 0;
  int i = 0;
  int n = 0;
  int sign = 0;
  int science_flag = 0;
  float_flags_t float_struct = {0};

  while ((isSeporator(**str) && f->specifier != 'c' && **str != '\0') ||
         (**str == skip && **str != '\0')) {
    (*str)++;
  }
  if (**str != '\0') {
    switch (f->specifier) {
      case 'd':
        while ((isDigit(**str) || checkSign(*str, &sign, f->width, DEC, i)) &&
               (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignInt(str_temp, var, f);
        break;
      case 'u':
        while ((isDigit(**str) || checkSign(*str, &sign, f->width, DEC, i)) &&
               (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignIntUnsigned(str_temp, var, f);
        break;
      case 'c':
        if (isAscii(**str)) {
          ch = **str;
          if (!f->asterics) assignChar(ch, var, f);
          (*str)++;
          break;
        } else {
          f->error = 1;
        }
      case 's':
        while ((f->width != 0 && !isSeporator(**str))) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignString(str_temp, var, f);
        break;
      case 'i':
        if (**str == '0') {
          (*str)++;
          if ((**str) == 'x' || (**str) == 'X') {
            (*str)++;
            while (
                (isHex(**str, 0) || checkSign(*str, &sign, f->width, HEX, i)) &&
                (f->width != 0)) {
              str_temp[i] = **str;
              (*str)++;
              i++;
              f->width--;
            }
            if (!i)
              f->error = 1;
            else if (!f->asterics)
              assignHex(str_temp, var, f);
          } else {
            while ((isOct(**str) || checkSign(*str, &sign, f->width, DEC, i)) &&
                   (f->width != 0)) {
              str_temp[i] = **str;
              (*str)++;
              i++;
              f->width--;
            }
            if (!i)
              f->error = 1;
            else if (!f->asterics)
              assignOct(str_temp, var, f);
          }
        } else {
          while ((isDigit(**str) || checkSign(*str, &sign, f->width, DEC, i)) &&
                 (f->width != 0)) {
            str_temp[i] = **str;
            (*str)++;
            i++;
            f->width--;
          }
          if (!i)
            f->error = 1;
          else if (!f->asterics)
            assignInt(str_temp, var, f);
        }
        break;

      case 'o':
        while ((isOct(**str) || checkSign(*str, &sign, f->width, OCT, i)) &&
               (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignOctUnsigned(str_temp, var, f);
        break;

      case 'x':
      case 'X':
        while (((isHex(**str, i + sign)) ||
                checkSign(*str, &sign, f->width, HEX, i)) &&
               (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignHexUnsigned(str_temp, var, f);
        break;

      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        if ((science_flag = checkScience(*str, f->width)) != 0) {
          *str = (*str) + 3;
          if (!f->asterics) assignScience(var, f, science_flag);
        } else {
          while (isFloat(**str, *(*str + 1), &float_struct) &&
                 (f->width != 0)) {  // добавить nan и inf
            str_temp[i] = **str;
            (*str)++;
            i++;
            f->width--;
          }
          if (!i)
            f->error = 1;
          else if (!f->asterics)
            assignFloat(str_temp, var, f);
        }
        break;

      case 'n':
        n = str_len - s21_strlen(*str);
        if (!f->asterics) assignN(n, var, f);
        break;

      case 'p':
        while ((isHex(**str, i)) && (f->width != 0)) {
          str_temp[i] = **str;
          (*str)++;
          i++;
          f->width--;
        }
        if (!i)
          f->error = 1;
        else if (!f->asterics)
          assignVoid(str_temp, var, f);
        break;

      case '%':
        if (**str == '%') {
          (*str)++;
          i++;
        }
        if (!i) f->error = 1;
        break;
    }
  } else {
    f->error++;
  }
}

int checkSign(const char *a, int *sign, int width, int base, int i) {
  int res = 0;
  if (!(*sign) && width != 1 && isSign(*a) && !i) {
    switch (base) {
      case HEX:
        if (isHex(*(a + 1), 0)) res = 1;
        break;
      case DEC:
        if (isDigit(*(a + 1))) res = 1;
        break;
      case OCT:
        if (isOct(*(a + 1))) res = 1;
        break;
    }
  }
  if (res) sign++;
  return res;
}

int checkScience(const char *str, int width) {
  int res = 0;
  if (width > 2 || width == -1) {
    if (*str == 'n' || *str == 'N')
      if (*(str + 1) == 'a' || *(str + 1) == 'A')
        if (*(str + 2) == 'n' || *(str + 2) == 'N') res = 1;
    if (*str == 'i' || *str == 'I')
      if (*(str + 1) == 'n' || *(str + 1) == 'N')
        if (*(str + 2) == 'f' || *(str + 2) == 'F') res = 2;
  }
  return res;
}

int isFloat(int a, int next, float_flags_t *fl) {
  int flag = 1;
  if (isDigit(a)) {
    fl->digit = 1;
  } else if ((fl->digit == 0 && fl->sign_before_e == 0 && fl->e == 0 &&
              fl->dot == 0 && (a == '-' || a == '+'))) {
    fl->sign_before_e++;
  } else if (fl->sign_before_e == 1 && fl->e == 0 && (a == '-' || a == '+')) {
    flag = 0;
  } else if (fl->sign_after_e == 0 && fl->digit && fl->e == 1 &&
             (a == '-' || a == '+')) {
    fl->sign_after_e++;
  } else if (fl->e == 1 && (a == '-' || a == '+') &&
             (fl->sign_after_e == 1 && !fl->digit)) {
    flag = 0;
  } else if (fl->digit == 1 && fl->e == 0 && (a == 'e' || a == 'E')) {
    fl->e++;
  } else if (fl->e == 0 && fl->dot == 0 && (a == '.') && isDigit(next)) {
    fl->dot++;
  } else {
    flag = 0;
  }
  return flag;
}

int isDigit(int a) { return (a >= '0' && a <= '9'); }

int isHex(int a, int i) {
  return ((a >= '0' && a <= '9') || (a >= 'a' && a <= 'f') ||
          (a >= 'A' && a <= 'F')) ||
         (a == 'x' && i == 1) || (a == 'X' && i == 1);
}

int isOct(int a) { return (a >= '0' && a <= '7'); }

int isAscii(int a) { return (a >= 0 && a <= 127); }

int isSeporator(int a) {
  return ((a == '\n') || (a == 32) || (a == '\0' || (a == '\t')));
}

int isSign(int a) { return (a == '+' || a == '-'); }

void assignHex(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = (short)s21_atohex(str);
  } else if (f->length == 'l') {
    *va_arg(var, long *) = s21_atohex(str);
  } else {
    *va_arg(var, int *) = (int)s21_atohex(str);
  }
}

void assignHexUnsigned(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, unsigned short *) = (unsigned short)s21_atohex(str);
  } else if (f->length == 'l') {
    *va_arg(var, unsigned long *) = s21_atohex(str);
  } else {
    *va_arg(var, unsigned int *) = (unsigned int)s21_atohex(str);
  }
}

void assignOct(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = (short)s21_ato8(str);
  } else if (f->length == 'l') {
    *va_arg(var, long *) = s21_ato8(str);
  } else {
    *va_arg(var, int *) = (int)s21_ato8(str);
  }
}

void assignOctUnsigned(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, unsigned short *) = (unsigned short)s21_ato8(str);
  } else if (f->length == 'l') {
    *va_arg(var, unsigned long *) = s21_ato8(str);
  } else {
    *va_arg(var, unsigned int *) = (unsigned int)s21_ato8(str);
  }
}

void assignIntUnsigned(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = (unsigned short)s21_atos(str);
  } else if (f->length == 'l') {
    *va_arg(var, long *) = s21_atol(str);
  } else {
    *va_arg(var, int *) = (unsigned int)s21_atoii(str);
  }
}

void assignInt(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'h') {
    *va_arg(var, short *) = (short)s21_atos(str);
  } else if (f->length == 'l') {
    *va_arg(var, long *) = s21_atol(str);
  } else {
    *va_arg(var, int *) = (int)s21_atoii(str);
  }
}

void assignVoid(char *str, va_list var, flags_t *f) {
  f->convertions++;
  void **dest = va_arg(var, void **);

  *dest = (void *)(0x0 + s21_usigned_atohex(str));
}

void assignN(int n, va_list var, flags_t *f) {
  if (f->length == 'h') {
    *va_arg(var, short *) = n;
  } else if (f->length == 'l') {
    *va_arg(var, long *) = n;
  } else {
    *va_arg(var, int *) = n;
  }
}

void assignFloat(char *str, va_list var, flags_t *f) {
  f->convertions++;
  if (f->length == 'l') {
    *va_arg(var, double *) = (double)s21_atoE(str);
  } else if (f->length == 'L') {
    *va_arg(var, long double *) = s21_atoE(str);
  } else {
    *va_arg(var, float *) = (float)s21_atoE(str);
  }
}

void assignScience(va_list var, flags_t *f, int flag) {
  f->convertions++;
  if (flag == 1) {
    if (f->length == 'l') {
      *va_arg(var, double *) = (double)NAN;
    } else if (f->length == 'L') {
      *va_arg(var, long double *) = NAN;
    } else {
      *va_arg(var, float *) = (float)NAN;
    }
  }
  if (flag == 2) {
    if (f->length == 'l') {
      *va_arg(var, double *) = (double)INFINITY;
    } else if (f->length == 'L') {
      *va_arg(var, long double *) = INFINITY;
    } else {
      *va_arg(var, float *) = (float)INFINITY;
    }
  }
}

void assignChar(char ch, va_list var, flags_t *f) {
  f->convertions++;
  *va_arg(var, char *) = ch;
}

void assignString(char *str, va_list var, flags_t *f) {
  f->convertions++;
  s21_strcpy(va_arg(var, char *), str);
}
