#include <ruby.h>
#include "extconf.h"

VALUE rb_RET_VAL(VALUE self, VALUE x) {
  int y = NUM2INT(x);
  return INT2NUM(y + 10);
}

void Init_foobar() {
  VALUE mod = rb_define_module("RubyGuides");
  rb_define_method(mod, "RET_VAL", rb_RET_VAL, 1);
}
