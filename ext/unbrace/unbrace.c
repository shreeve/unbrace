#include "ruby/ruby.h"
// #include "ruby/debug.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

int brace_expand(const char *str) {
  const char *p = str;
  const char *pend = p + strlen(p);
  const char *s = p;
  const char *lbrace = 0, *rbrace = 0;
  int nest = 0, status = 0;

  while (*p) {
    if (*p == '{' && nest++ == 0) {
      lbrace = p;
    }
    if (*p == '}' && lbrace && --nest == 0) {
      rbrace = p;
      break;
    }
    if (*p == '\\' && !*++p) {
      break;
    }
    p++;
  }

  if (lbrace && rbrace) {
    size_t len = strlen(s) + 1;
    char *buf = (char *) malloc(len);
    long shift;

    if (!buf) return -1;
    memcpy(buf, s, lbrace-s);
    shift = (lbrace-s);
    p = lbrace;
    while (p < rbrace) {
      const char *t = ++p;
      nest = 0;
      while (p < rbrace && !(*p == ',' && nest == 0)) {
        if (*p == '{') nest++;
        if (*p == '}') nest--;
        if (*p == '\\' && (++p == rbrace)) break;
        p++;
      }
      memcpy(buf+shift, t, p-t);
      strlcpy(buf+shift+(p-t), rbrace+1, len-(shift+(p-t)));
      status = brace_expand(buf);
    }
    free(buf);
  }
  else if (!lbrace && !rbrace) {
    printf("%s\n", str);
    status = 1;
  }

  return status;
}

static VALUE
unbrace(VALUE self, VALUE item)
{
  // return rb_debug_inspector_open(callback, (void *) &item);
  printf("Hey cheetyburg...\n");
}

void
Init_unbrace(VALUE self)
{
  VALUE cString = rb_define_class("String", rb_cObject);
  rb_define_singleton_method(cString, "unbrace", unbrace, 1);
  rb_define_method(cString, "unbrace", unbrace, 1);
}

// int main(int argc, char *argv[]) {
//   if (argc > 1) {
//     brace_expand(argv[1]);
//   }
//   return 0;
// }
