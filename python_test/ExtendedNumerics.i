%module numeric
%{
  #include "../src/ExtendedNumerics.hpp"
  #include <string>
%}

%define SWIGGING_EXTENSION %enddef
%include "std_string.i"
%rename(print_numeric) operator <<;
%rename(num_add) operator +;
%rename(num_sub) operator -;
%rename(num_mul) operator *;
%rename(num_div) operator /;
%rename(num_eq) operator ==;
%rename(num_uneq) operator !=;
%rename(num_lt) operator <;
%include "../src/ExtendedNumerics.hpp"

%extend Numeric {
  std::string __str__() {
    return $self->str();
  }
}
