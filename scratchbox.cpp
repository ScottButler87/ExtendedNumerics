

#include "src/ExtendedNumerics.hpp"
#include "src/util.hpp"

int main() {
  // log2_64(MIN_FIXNUM_VALUE)
  Numeric a("17340000000");
  Numeric b(-867295464195.8511, 79900071139.40796);
  Numeric expected(-50.01703945766154, 4.607847239873585);

  Numeric z = b / a;
  std::cout << z << std::endl << std::endl;

}