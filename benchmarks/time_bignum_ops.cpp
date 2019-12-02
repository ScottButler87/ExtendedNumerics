#include "benchmark_settings_and_defs.hpp"
#include "time_bignum_ops.hpp"
#include <sstream>

int main() {
  if (!BE_SILENT) STATE_WARMING_CONDITIONS

  std::cout << "Results will be printed at the end of all benchmarking." << std::endl << std::endl;

  std::ostringstream results;

  add_result_bignum_addition_doubling_behavior(results);
  add_result_bignum_subtraction_doubling_behavior(results);
  add_result_bignum_multiplication_doubling_behavior(results);
  add_result_bignum_division_doubling_behavior(results);

  std::cout << std::endl << "RESULTS" << std::endl << std::endl << results.str();
}

