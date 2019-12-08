%module numeric
%{
  #include "../src/ExtendedNumerics.hpp"
  #include <string>
%}

%define SWIGGING_EXTENSION %enddef
%rename(print_numeric) operator <<;
%rename(int_add) operator +;
%rename(int_sub) operator -;
%rename(int_div) operator /;
%include "std_string.i"
%include "../src/ExtendedNumerics.hpp"

%extend Numeric {
  std::string __str__() {
    return $self->str();
  }
}
