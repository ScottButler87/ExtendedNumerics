#include <iostream>
#include <iomanip>
#include "benchmark_settings_and_defs.hpp"
#include "random_numeric_generators.hpp"
#include "time_benchmark_operation.hpp"
#include "../src/ExtendedNumerics.hpp"

#include "benchmark_perf_per_operand_type.hpp"

int main() {
  if (!BE_SILENT) STATE_WARMING_CONDITIONS

  std::cout << "Results will be printed at the end of all benchmarking." << std::endl << std::endl;

  std::ostringstream results;

  add_result_fixnum_performance_per_operand_type(results);
  add_result_bignum_performance_per_operand_type(results);
  add_result_ratnum_performance_per_operand_type(results);
  add_result_exact_complexnum_performance_per_operand_type(results);
  add_result_inexact_complexnum_performance_per_operand_type(results);

  std::cout << std::endl << "RESULTS" << std::endl << std::endl << results.str();

  return 0;
}
