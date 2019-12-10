
#include <sstream>
#include "src/Numeric.hpp"
#include "src/util.hpp"

int main() {
  // log2_64(MIN_FIXNUM_VALUE)
  Numeric left("2198825287302845906");
//  Numeric right("-92157563935128028594646977543127802971174372583734327898660469179474947359309", "64275066979598845098360593596430668846639352943449524220918527004357292439331", "-83170615071665878149854206075674423558328488156085318047834429258680864487017", "101596459022879761283924244764214856126866367176974142192943467646362121395010");
  Numeric right("111071447468899776113639802799525349118795768311325784036753511012834079114927");
  bool result = left < right;
  std::stringstream ss;
  ss << result << std::endl;
  std::string temp = ss.str();
  std::cout << temp << std::endl;
}