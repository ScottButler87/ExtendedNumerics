%module numeric
%{
  #include "../src/ExtendedNumerics.hpp"
  #include "../src/Numeric.hpp"
  #include "../src/util.hpp"
%}

%define SWIGGING_EXTENSION %enddef
%rename(print_numeric) operator <<;
%rename(num_add) operator +;
%rename(num_sub) operator -;
%rename(num_mul) operator *;
%rename(num_div) operator /;
%rename(num_eq) operator ==;
%rename(num_uneq) operator !=;
%rename(num_lt) operator <;
%include <std_string.i>
%include "../src/util.hpp"
%include "../src/ExtendedNumerics.hpp"
%include "../src/Numeric.hpp"

%extend Numeric {
  std::string __str__() {
    return $self->str();
  }
}
