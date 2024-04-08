#include "git-compat-util.h"
#include "config.h"

#define myenter(...) __myenter(__func__, __VA_ARGS__);
#define myexit(...) __myexit(__func__, __VA_ARGS__);

void __myenter(const char *func, const char *fmt, ...);
void __myexit(const char *func, const char *fmt, ...);

void myprintf(const char *fmt, ...);

void increase_indent();
void decrease_indent();
