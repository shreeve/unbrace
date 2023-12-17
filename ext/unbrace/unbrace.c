// ============================================================================
// Summary: unbrace.c - Offers String#unbrace, which expands braces in strings.
// Version: 0.5.0
//  Author: Steve Shreeve (steve.shreeve@gmail.com)
//    Date: December 16, 2023
//   Legal: Same license as Ruby (see http://www.ruby-lang.org/en/LICENSE.txt)
//    Note: This file is derived from "dir.c" in the Ruby source code.
// ============================================================================

#include "ruby/ruby.h"
// FIXME: Encoding requires(?) others, such as #include "ruby/encoding.h"

static void
brace_expand(const char *str, VALUE ary) // FIXME: Add ",rb_encoding *enc)" here?
{
    const char *p = str;
    const char *pend = p + strlen(p);
    const char *s = p;
    const char *lbrace = 0, *rbrace = 0;
    int nest = 0;

    while (*p) {
        if (*p == '\\' && !*++p) break;
        if (*p == '{' && nest++ == 0) lbrace = p;
        if (*p == '}' && lbrace && --nest == 0) {
            rbrace = p;
            break;
        }
        p++; // FIXME: For encoding, use Inc(p, pend, enc) here?
    }

    if (lbrace && rbrace) {
        long size = lbrace - s;
        size_t len = strlen(s) + 1;
        char *buf = (char *) malloc(len); // FIXME: Use ALLOC_N(...) here?
        if (!buf) return;

        memcpy(buf, s, size);
        p = lbrace;
        while (p < rbrace) {
            const char *t = ++p;
            nest = 0;
            while (p < rbrace && !(*p == ',' && nest == 0)) {
                if (*p == '\\' && (++p == rbrace)) break;
                if (*p == '{') nest++;
                if (*p == '}') nest--;
                p++; // FIXME: For encoding, use Inc(p, pend, enc) here?
            }
            memcpy(buf + size, t, p - t);
            strlcpy(buf + size + (p - t), rbrace + 1, len - (size + (p - t)));
            brace_expand(buf, ary);
        }
        free(buf); // FIXME: Use GLOB_FREE(buf) here?
    }
    else if (!lbrace && !rbrace) {
        rb_ary_push(ary, rb_str_new_cstr(str));
    }
}

static VALUE
rb_str_unbrace(VALUE str)
{
    if (!rb_block_given_p()) {
        VALUE ary = rb_ary_new();
        brace_expand(RSTRING_PTR(str), ary);
        return ary;
    }
    else {
        return Qnil;
    }
}

void
Init_unbrace(void)
{
    VALUE rb_cString = rb_define_class("String", rb_cObject);
    rb_define_method(rb_cString, "unbrace", rb_str_unbrace, 0);
}
