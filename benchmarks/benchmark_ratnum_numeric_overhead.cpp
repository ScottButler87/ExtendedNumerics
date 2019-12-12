#include "benchmark_ratnum_numeric_overhead.hpp"
#include <sstream>

int main() {
  std::stringstream results;
  add_result_ratnum_numeric_overhead(results);
  std::cout << results.str() << std::endl << std::flush;
}