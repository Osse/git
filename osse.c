#include "osse.h"

#include <stdio.h>
#include <stdarg.h>

#define STEP 4
static int indent = -STEP;

void __myenter(const char *f, const char *fmt, ...)
{
	va_list ap;
	increase_indent();

	printf("%*sEntering %s", indent, "", f);
	if (fmt && strlen(fmt))
		putchar('(');

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	if (fmt && strlen(fmt))
		putchar(')');
	puts("");
}

void __myexit(const char *func, const char *fmt, ...)
{
	va_list ap;

	printf("%*sExiting %s()", indent, "", func);
	if (fmt && strlen(fmt)) {
		putchar(':');
		putchar(' ');
	}

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	puts("");

	decrease_indent();
}

void myprintf(const char *fmt, ...)
{
	va_list ap;
	printf("%*s", indent, "");

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}

void increase_indent()
{
	indent += STEP;
}

void decrease_indent()
{
	indent -= STEP;
}
