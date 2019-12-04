#include "benchmark_settings_and_defs.hpp"
#include "time_bignum_ops.hpp"
#include "time_ratnum_ops.hpp"
#include "time_exact_complexnum_ops.hpp"
#include "benchmark_perf_per_operand_type.hpp"

int main() {
  if (!BE_SILENT) STATE_WARMING_CONDITIONS

    std::cout << "Results will be printed at the end of all benchmarking." << std::endl << std::endl;

  std::ostringstream results;

//  add_result_bignum_doubling_behavior(results);
//
//  add_result_ratnum_doubling_behavior(results);
//
//  add_result_exact_complexnum_doubling_behavior(results);

  add_results_performance_per_operation_and_operand_type(results);

  std::cout << std::endl << "RESULTS" << std::endl << std::endl << results.str();

  return 0;
}

