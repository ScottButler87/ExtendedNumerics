#include "benchmark_settings_and_defs.hpp"
#include "time_ratnum_ops.hpp"
#include <sstream>

int main() {
  if (!BE_SILENT) STATE_WARMING_CONDITIONS

    std::cout << "Results will be printed at the end of all benchmarking." << std::endl << std::endl;

  std::ostringstream results;

  add_result_ratnum_addition_doubling_behavior(results);
  add_result_ratnum_subtraction_doubling_behavior(results);
  add_result_ratnum_multiplication_doubling_behavior(results);
  add_result_ratnum_division_doubling_behavior(results);

  std::cout << std::endl << "RESULTS" << std::endl << std::endl << results.str();

  return 0;
}
