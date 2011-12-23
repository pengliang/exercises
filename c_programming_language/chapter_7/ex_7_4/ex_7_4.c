#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

static const int kFormatLen = 100;

/* Minimal scanf with variable argument list */
int MiniScanf(char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  char local_fmt[kFormatLen];
  int i = 0, *ival;
  unsigned *uval;
  double *dval;

  va_start(ap, fmt);

  for (p = fmt; *p; ++p) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    i = 0;
    local_fmt[i++] = '%';
    while (*(p+1) && !isalpha(*(p+1))) {
      local_fmt[i++] = *++p;
    }
    local_fmt[i++] = *(p+1);
    local_fmt[i] = '\0';

    switch (*++p) {
      case 'd':
      case 'i':
        ival = va_arg(ap, int *);
        scanf(local_fmt, ival);
        break;
      case 'x':
      case 'X':
      case 'u':
      case 'o':
        uval = va_arg(ap, unsigned *);
        scanf(local_fmt, uval);
        break;
      case 'f':
        dval = va_arg(ap, double *);
        scanf(local_fmt, dval);
        break;
      case 's':
        sval = va_arg(ap, char *);
        scanf(local_fmt, sval);
        break;
      default:
        scanf(local_fmt);
        break;
    }
  }
  va_end(ap);
}
