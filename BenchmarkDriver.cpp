#include <iostream>
#include "src/ExtendedNumerics.hpp"

#define STR_GT(str, str2) std::cout << str << " greater than " << str2 << " " << ((str > str2) ? "true" : "false") << std::endl

int main(int argc, char **argv) {
  Numeric big("128282828282828282828828282828282828");
  Numeric rat("1", "2");
  Numeric zero("0");
  Numeric test("0", "1", "-12", "1");
  cpp_rational a(cpp_int("1"), cpp_int("6"));
  cpp_rational b(cpp_int("1"), cpp_int("5"));
  std::cout << (a < b) << std::endl;
  std::cout << big + test << std::endl;
  std::cout << (static_cast<double>(cpp_int("12323")) + 0.87) << std::endl;
  return 0;
}


//static std::string MAX_POSITIVE_FIXNUM_STRING("4611686018427387903");
//static std::string MAX_NEGATIVE_FIXNUM_STRING("-4611686018427387904");