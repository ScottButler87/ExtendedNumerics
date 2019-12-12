#include <iostream>
#include <iomanip>
#include "_benchmark_settings_and_defs.hpp"
#include "random_numeric_generators.hpp"
#include "time_benchmark_operation.hpp"
#include "../src/Numeric.hpp"

#include "benchmark_perf_per_operand_type.hpp"

int main() {
  if (!BE_SILENT) STATE_WARMING_CONDITIONS

  std::cout << "Results will be printed at the end of all benchmarking." << std::endl << std::endl;

  std::ostringstream results;

  add_results_performance_per_operation_and_operand_type(results);

  std::cout << std::endl << "RESULTS" << std::endl << std::endl << results.str();

  return 0;
}
