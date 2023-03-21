#include "s21_sprintf.h"

#include "s21_string.h"
#define SIZE 512
#include <limits.h>
// A format specifier for print functions follows this prototype:
// %[flags][width][.precision][length]specifier

// int main() {
//   start();
//   return 0;
// }

// void start() {
//   char str1[SIZE] = {'\0'};
//   char str2[SIZE] = {'\0'};
//   char format[] = "%3.1G";
//   double val = 0.000005;
//   int a = 0;
//   int b = 0;
//   a = s21_sprintf(str1, format, val);
//   b = sprintf(str2, format, val);
//   printf("s21_sprintf: %d\n", a);
//   printf("sprintf: %d\n", b);
//   printf("s21_sprintf: %sEND\n", str1);
//   printf("origsprintf: %sEND\n", str2);
// }

int s21_sprintf(char *str, const char *format, ...) {
  va_list var;
  va_start(var, format);
  char *strStart = str;
  while (*format) {
    flags flag = {0};
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;
      format = parse_Format(format, &flag, var);
      str = specifier(str, &flag, var);
      if (flag.specifier == 'n') {
        int *pointer = va_arg(var, int *);
        *pointer = str - strStart;
      }
    }
  }
  va_end(var);
  return str - strStart;
}

const char *parse_Format(const char *format, flags *f, va_list var) {
  format = parseFlags(format, f);
  format = parse_Width(format, f, var);
  format = parsePrecision(format, f, var);
  format = parse_Length(format, f);
  f->specifier = *format;
  format++;
  return format;
}

const char *parseFlags(const char *format, flags *f) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '#' ||
         *format == '0') {
    switch (*format) {
      case '-':
        f->minus = true;
        break;
      case '+':
        f->plus = true;
        break;
      case ' ':
        f->space = true;
        break;
      case '#':
        f->hashtag = true;
        break;
      case '0':
        f->zero = true;
        break;
    }
    format++;
  }
  return format;
}

const char *parse_Width(const char *format, flags *f, va_list var) {
  if (*format == '*') {
    format++;
    f->width = va_arg(var, int);
  } else if (*format >= 48 && *format <= 57) {
    char tempWidth[BUFFER_SIZE] = "";
    for (int i = 0; *format >= 48 && *format <= 57; i++, format++) {
      tempWidth[i] = *format;
    }
    f->width = s21_atoisprint(tempWidth);
  }
  return format;
}

const char *parsePrecision(const char *format, flags *f, va_list var) {
  if (*format == '.') {
    f->isPrecisionSet = true;
    format++;
    if (*format == '*') {
      format++;
      f->precision = va_arg(var, int);
    } else if (*format >= 48 && *format <= 57) {
      char tempPrecision[BUFFER_SIZE] = "";
      for (int i = 0; *format >= 48 && *format <= 57; i++, format++) {
        tempPrecision[i] = *format;
      }
      f->precision = s21_atoisprint(tempPrecision);
    } else {
      f->precision = -1;
    }
  }
  return format;
}

const char *parse_Length(const char *format, flags *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
      break;
    case 'L':
      f->length = 'L';
      format++;
      break;
  }
  return format;
}

char *specifier(char *str, flags *flag, va_list var) {
  char buffer[BUFFER_SIZE] = "\0";
  if (flag->specifier == 'd' || flag->specifier == 'i') {
    integerSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'u') {
    unsignedSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'o') {
    octalSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'f') {
    floatSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'p') {
    pointerSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'e' || flag->specifier == 'E') {
    exponentSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'g' || flag->specifier == 'G') {
    // if (flag->precision == -1) flag->precision = 0;
    gSpecifier(buffer, flag, var);
  } else if (flag->specifier == 'x' || flag->specifier == 'X') {
    hexSpecifier(buffer, flag, var);
  } else if (flag->specifier == 's') {
    if (flag->length == 'l') {
      widthStringSpecifier(buffer, flag, var);
    } else {
      stringSpecifier(buffer, flag, var);
    }
  } else if (flag->specifier == 'c') {
    if (flag->length == 'l') {
      widthCharSpecifier(buffer, flag, var);
    } else {
      charSpecifier(buffer, flag, var);
    }
  } else if (flag->specifier == 'n') {
  } else {
    buffer[0] = flag->specifier;
  }
  if (flag->specifier == 'G' || flag->specifier == 'X' ||
      flag->specifier == 'E') {
    toUpper(buffer);
  }

  for (s21_size_t i = 0; i < s21_strlen(buffer); i++) {
    *str = buffer[i];
    str++;
  }
  *str = '\0';
  return str;
}

void charSpecifier(char *buffer, flags *flag, va_list var) {
  char ch = va_arg(var, int);
  if (flag->minus && flag->width) {
    buffer[0] = ch;
    for (int i = 1; i < flag->width; i++) {
      buffer[i] = ' ';
    }
  } else if (flag->width) {
    for (int i = 0; i < flag->width; i++) {
      if (i == flag->width - 1) {
        buffer[i] = ch;
      } else {
        buffer[i] = ' ';
      }
    }
  } else {
    buffer[0] = ch;
  }
}

void widthCharSpecifier(char *buffer, flags *flag, va_list var) {
  wchar_t ch = va_arg(var, wchar_t);
  if (flag->minus && flag->width) {
    wcstombs(buffer, &ch, BUFFER_SIZE);
    for (int i = s21_strlen(buffer); i < flag->width; i++) {
      buffer[i] = ' ';
    }
  } else if (flag->width) {
    char temp[BUFFER_SIZE] = "";
    wcstombs(temp, &ch, BUFFER_SIZE);  // ? нельзя
    for (size_t i = 0; i < flag->width - s21_strlen(temp); i++) {
      buffer[i] = ' ';
    }
    s21_strcat(buffer, temp);
  } else {
    wcstombs(buffer, &ch, BUFFER_SIZE);
  }
}

void stringSpecifier(char *buffer, flags *flag, va_list var) {
  char *input = va_arg(var, char *);
  char tempInput[BUFFER_SIZE] = "";
  s21_strcpy(tempInput, input);
  if (flag->isPrecisionSet) {
    tempInput[flag->precision] = '\0';
  }

  int shift = flag->width - s21_strlen(tempInput);
  int lengthInput = s21_strlen(tempInput);

  if (flag->minus && shift > 0) {
    s21_strcpy(buffer, tempInput);
    s21_memset(buffer + lengthInput, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tempInput);
  } else {
    s21_strcpy(buffer, tempInput);
  }
}

void widthStringSpecifier(char *buffer, flags *flag, va_list var) {
  wchar_t *input = va_arg(var, wchar_t *);
  char tempInput[BUFFER_SIZE] = "";
  char fromWcharToChar[BUFFER_SIZE] = "";
  wcstombs(fromWcharToChar, input, BUFFER_SIZE);
  s21_strcpy(tempInput, fromWcharToChar);
  if (flag->isPrecisionSet) {
    tempInput[flag->precision] = '\0';
  }

  int shift = flag->width - s21_strlen(tempInput);
  int lengthInput = s21_strlen(tempInput);

  if (flag->minus && shift > 0) {
    s21_strcpy(buffer, tempInput);
    s21_memset(buffer + lengthInput, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buffer, ' ', shift);
    s21_strcpy(buffer + shift, tempInput);
  } else {
    s21_strcpy(buffer, tempInput);
  }
}

void integerSpecifier(char *buffer, flags *flag, va_list var) {
  int64_t num = va_arg(var, int64_t);

  if (flag->length == 0) {
    num = (int32_t)num;
  } else if (flag->length == 'h') {
    num = (int16_t)num;
  }

  integerToString(buffer, num, 10);
  formatPrecision(buffer, flag);
  formatFlags(buffer, flag);
}

/// ?DELETE?
int numsCount(int64_t num) {
  // count of digits in number
  int result = 0;
  if (!num) {
    result = 1;
  } else {
    while (num) {
      num /= 10;
      result++;
    }
  }
  return result;
}
/// ?DELETE?

void integerToString(char *buffer, int64_t num, int notation) {
  char temp[BUFFER_SIZE] = {'\0'};
  int sign = 0;
  bool negative = num < 0 ? true : false;
  num = negative ? -num : num;
  if (!num) {
    buffer[0] = '0';
  }
  while (num) {
    temp[sign] = "0123456789abcdef"[num % notation];
    num /= notation;
    sign++;
  }
  if (negative) {
    temp[sign] = '-';
  }
  int len = s21_strlen(temp);
  for (int i = 0, j = len - 1; i < len; i++, j--) {
    buffer[i] = temp[j];
  }
}

void unsignedToString(char *buffer, uint64_t num, int notation) {
  char temp[BUFFER_SIZE] = "";
  int sign = 0;
  if (!num) {
    buffer[0] = '0';
  }
  while (num) {
    temp[sign] = "0123456789abcdef"[num % notation];
    num /= notation;
    sign++;
  }
  int len = s21_strlen(temp);
  for (int i = 0, j = len - 1; i < len; i++, j--) {
    buffer[i] = temp[j];
  }
}

void formatPrecision(char *buffer, flags *flag) {
  char temp[BUFFER_SIZE] = "";
  int len = s21_strlen(buffer);
  int sign = 0;
  if (buffer[0] == '-') {
    temp[0] = '-';
    sign = 1;
    len--;
  }

  if (flag->precision > len) {
    int i;
    for (i = sign; i < flag->precision - len + sign; i++) {
      temp[i] = '0';
    }
    for (int j = sign; buffer[j]; j++, i++) {
      temp[i] = buffer[j];
    }
    s21_strcpy(buffer, temp);
  }

  bool isInteger = flag->specifier == 'd' || flag->specifier == 'i' ||
                   flag->specifier == 'o' || flag->specifier == 'u' ||
                   flag->specifier == 'x' || flag->specifier == 'X';

  if (flag->isPrecisionSet && flag->precision == 0 && isInteger &&
      buffer[0] == '0') {
    buffer[0] = '\0';
  }
}

void formatFlags(char *buffer, flags *flag) {
  char temp[BUFFER_SIZE] = "";
  if (flag->plus && flag->specifier != 'u' && flag->specifier != 'p') {
    temp[0] = buffer[0] == '-' ? '-' : '+';
    s21_strcpy(temp + 1, buffer[0] == '-' ? buffer + 1 : buffer);
    s21_strcpy(buffer, temp);
  } else if (flag->space && buffer[0] != '-' && flag->specifier != 'u' &&
             flag->specifier != 'p') {
    temp[0] = ' ';
    s21_strcpy(temp + 1, buffer);
    s21_strcpy(buffer, temp);
  }
  if (flag->width > (int)s21_strlen(buffer)) {
    int diff = flag->width - s21_strlen(buffer);
    if (flag->minus) {
      s21_strcpy(temp, buffer);
      s21_memset(temp + s21_strlen(buffer), ' ', diff);
    } else {
      s21_memset(temp, flag->zero ? '0' : ' ', diff);
      s21_strcpy(temp + diff, buffer);
    }
    s21_strcpy(buffer, temp);
  }
}

void unsignedSpecifier(char *buffer, flags *flag, va_list var) {
  uint64_t num = va_arg(var, uint64_t);

  if (flag->length == 0) {
    num = (uint32_t)num;
  } else if (flag->length == 'h') {
    num = (uint16_t)num;
  }

  unsignedToString(buffer, num, 10);
  formatPrecision(buffer, flag);
  formatFlags(buffer, flag);
}

void floatSpecifier(char *buffer, flags *flag, va_list var) {
  long double num;
  if (flag->length == 'L') {
    num = va_arg(var, long double);
  } else {
    num = va_arg(var, double);
  }

  if (!flag->isPrecisionSet) {
    flag->precision = 6;
  }

  doubleToString(buffer, num, flag);
  formatFlags(buffer, flag);
}

void doubleToString(char *buffer, long double num, flags *flag) {
  if ((flag->precision == -1 || flag->precision == 0) &&
      (flag->specifier == 'e' || flag->specifier == 'E')) {
    num = round(num);
    *buffer = digitToAscii((int)num);
  } else if (flag->precision == -1 && flag->specifier == 'f' && num < 10) {
    num = round(num);
    *buffer = digitToAscii((int)num);
  } else {
    char temp[BUFFER_SIZE] = "";
    int sign = 0;
    int notation = 10;
    bool negative = num < 0 ? true : false;
    num = negative ? -num : num;
    long double tempNum = num;
    while (tempNum) {
      if (tempNum < 1) {
        break;
      }
      temp[sign] = digitToAscii((int)fmod(tempNum, notation));
      tempNum /= notation;
      sign++;
    }
    if (negative) {
      temp[sign] = '-';
    }
    int len = s21_strlen(temp);
    int index = 0;
    for (int j = len - 1; index < len; index++, j--) {
      buffer[index] = temp[j];
    }
    if (index == 0 || (negative && index == 1)) {
      buffer[index++] = '0';
      if (flag->specifier == 'g' || flag->specifier == 'G') flag->precision++;
    }
    int tempIndex = index;
    buffer[index++] = '.';
    char tempRightPart[BUFFER_SIZE] = "";
    long double l = 0, r = modfl(num, &l);
    for (int p = 0; p < flag->precision; p++) {
      r = r * 10;
      tempRightPart[p] = digitToAscii(((int)r) % 10);
    }
    long long rightPart = roundl(r);
    if (!rightPart) {
      for (int i = 0; i < flag->precision; i++) {
        buffer[index++] = '0';
      }
    } else {
      int len = s21_strlen(tempRightPart);
      for (int i = len, j = 0; rightPart || i > 0; rightPart /= 10, i--, j++) {
        tempRightPart[j] = digitToAscii((int)(rightPart % 10 + 0.5));
      }
      for (int i = len; i > 0; i--) {
        buffer[index++] = tempRightPart[i - 1];
      }
    }
    if (tempIndex == index - 1 && !flag->hashtag) {
      buffer[tempIndex] = '\0';
    }
  }
}

char digitToAscii(int a) { return 48 + a; }

int asciiToDigit(char a) { return a - 48; }

void exponentSpecifier(char *buffer, flags *flag, va_list var) {
  long double num;
  if (flag->length == 'L') {
    num = va_arg(var, long double);
  } else {
    num = va_arg(var, double);
  }

  int pow = 0;
  char sign = (int)num == 0 ? '-' : '+';

  if ((int)num - num) {
    while ((int)num == 0) {
      pow++;
      num *= 10;
    }
  } else {
    sign = '+';
  }
  while ((int)num / 10 != 0) {
    pow++;
    num /= 10;
  }

  if (!flag->isPrecisionSet) {
    flag->precision = 6;
  }

  doubleToString(buffer, num, flag);
  putExponentToString(buffer, pow, sign);
  formatFlags(buffer, flag);
}

void putExponentToString(char *buffer, int pow, char sign) {
  int len = s21_strlen(buffer);
  buffer[len] = 'e';
  buffer[len + 1] = sign;
  buffer[len + 3] = digitToAscii(pow % 10);
  pow /= 10;
  buffer[len + 2] = digitToAscii(pow % 10);
  buffer[len + 4] = '\0';
}

void toUpper(char *buffer) {
  for (s21_size_t i = 0; i < s21_strlen(buffer); i++) {
    if (buffer[i] >= 97 && buffer[i] <= 122) {
      buffer[i] -= 32;
    }
  }
}

void octalSpecifier(char *buffer, flags *flag, va_list var) {
  buffer[0] = '0';
  int64_t num = va_arg(var, int64_t);
  integerToString(buffer + flag->hashtag, num, 8);
  formatPrecision(buffer, flag);
  formatFlags(buffer, flag);
}

void hexSpecifier(char *buffer, flags *flag, va_list var) {
  uint64_t num = va_arg(var, uint64_t);

  if (flag->length == 0) {
    num = (uint32_t)num;
  } else if (flag->length == 'h') {
    num = (uint16_t)num;
  }
  unsignedToString(buffer, num, 16);
  formatPrecision(buffer, flag);
  if (flag->hashtag) {
    insertDecimalOx(buffer, flag);
  }
  formatFlags(buffer, flag);
}

void insertDecimalOx(char *buffer, flags *flag) {
  s21_size_t isAllDigitsIsZeroes = 0;
  for (int i = 0; buffer[i]; i++) {
    if (buffer[i] == '0') {
      isAllDigitsIsZeroes++;
    }
  }
  if (((isAllDigitsIsZeroes != s21_strlen(buffer)) || flag->specifier == 'p') &&
      flag->specifier != 'x' && flag->specifier != 'X') {
    s21_memmove(buffer + 2, buffer, s21_strlen(buffer));
    buffer[0] = '0';
    buffer[1] = 'x';
  }
  if ((isAllDigitsIsZeroes != s21_strlen(buffer)) && flag->specifier == 'x') {
    s21_memmove(buffer + 2, buffer, s21_strlen(buffer));
    buffer[0] = '0';
    buffer[1] = 'x';
  }
  if ((isAllDigitsIsZeroes != s21_strlen(buffer)) && flag->specifier == 'X') {
    s21_memmove(buffer + 2, buffer, s21_strlen(buffer));
    buffer[0] = '0';
    buffer[1] = 'X';
  }
}

void pointerSpecifier(char *buffer, flags *flag, va_list var) {
  unsignedToString(buffer, va_arg(var, uint64_t), 16);
  formatPrecision(buffer, flag);
  insertDecimalOx(buffer, flag);
  formatFlags(buffer, flag);
}

void gSpecifier(char *buffer, flags *flag, va_list var) {
  long double num;
  if (flag->length == 'L') {
    num = va_arg(var, long double);
  } else {
    num = va_arg(var, double);
  }

  if (!flag->isPrecisionSet) {
    flag->precision = 6;
  }
  if (flag->precision == 0) {
    flag->precision = 1;
  }

  int digitCount = numsCount((int)num);
  if (digitCount > flag->precision) {
    int pow = 0;
    char sign = (int)num == 0 ? '-' : '+';
    if ((int)num - num) {
      while ((int)num == 0) {
        pow++;
        num *= 10;
      }
    } else {
      sign = '+';
    }
    while ((int)num / 10 != 0) {
      pow++;
      num /= 10;
    }
    flag->precision--;

    if (pow > 0 && pow < 5) flag->precision = pow;
    doubleToString(buffer, num, flag);
    // } else {
    //   doubleToString(buffer, num, flag);
    putExponentToString(buffer, pow, sign);
    // }
  } else {
    flag->precision = flag->precision - digitCount;
    doubleToString(buffer, num, flag);
  }

  if (!flag->hashtag) {
    deleteZeroesFromEnd(buffer);
  }
  formatFlags(buffer, flag);
}

void deleteZeroesFromEnd(char *buffer) {
  int len = s21_strlen(buffer);
  char temp[BUFFER_SIZE] = "";
  for (int i = 0; i < len; i++) {
    temp[i] = buffer[len - i - 1];
  }
  int i = 0;
  for (; i < len; i++) {
    if (temp[i] == '0') {
      buffer[len - i - 1] = '\0';
    } else {
      break;
    }
  }
  if (buffer[len - i - 1] == '.') {
    buffer[len - i - 1] = '\0';
  }
}

// void PutgForShortDigit(char *buffer, int pow, long double num) {
//   s21_size_t i = 0;
//   bool negative = num < 0 ? true : false;
//   if (negative) {
//     buffer[i] = '-';
//     i++;
//   }
//   buffer[i] = '0';
//   i++;
//   buffer[i] = '.';
//   i++;
//   while (pow > 0) {
//     buffer[i] = '0'
//   }
// }

int s21_atoisprint(char *str) {
  int atoint = 0;
  int sign = 1;  //если подают отрицательное число
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atoint = atoint * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atoint *= sign;
  return (atoint);
}