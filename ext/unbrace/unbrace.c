#include "ruby/ruby.h"
// FIXME: Encoding requires(?) others, such as #include "ruby/encoding.h"

static int
brace_expand(const char *str) // FIXME: Add ",rb_encoding *enc)" here?
{
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
        p++; // FIXME: For encoding, use Inc(p, pend, enc) here?
    }

    if (lbrace && rbrace) {
        size_t len = strlen(s) + 1;
        char *buf = (char *) malloc(len); // FIXME: Use ALLOC_N(...) here?
        long shift;

        if (!buf) return -1;
        memcpy(buf, s, lbrace - s);
        shift = (lbrace - s);
        p = lbrace;
        while (p < rbrace) {
            const char *t = ++p;
            nest = 0;
            while (p < rbrace && !(*p == ',' && nest == 0)) {
                if (*p == '{') nest++;
                if (*p == '}') nest--;
                if (*p == '\\' && (++p == rbrace)) break;
                p++; // FIXME: For encoding, use Inc(p, pend, enc) here?
            }
            memcpy(buf + shift, t, p - t);
            strlcpy(buf + shift + (p - t), rbrace + 1, len - (shift + (p - t)));
            status = brace_expand(buf);
        }
        free(buf); // FIXME: Use GLOB_FREE(buf) here?
    }
    else if (!lbrace && !rbrace) {
        printf("%s\n", str);
        status = 1;
    }

    return status;
}

static VALUE
rb_str_unbrace(VALUE self, VALUE item)
{
    brace_expand("lawyer_{name,{work,home}_email_{active,inactive},state}");
    // FIXME: How do we return the ary VALUE?
}

void
Init_unbrace(VALUE self)
{
    VALUE rb_cString = rb_define_class("String", rb_cObject);
    rb_define_method(rb_cString, "unbrace", rb_str_unbrace, 0);
}
