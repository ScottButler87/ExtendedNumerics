%module numeric
%{
  #define SWIG_FILE_WITH_INIT
  #include "../src/ExtendedNumerics.hpp"
  #include <string>
%}

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
