#include "_benchmark_settings_and_defs.hpp"
#include "time_bignum_ops.hpp"
#include "time_ratnum_ops.hpp"
#include "time_exact_complexnum_ops.hpp"
#include "benchmark_perf_per_operand_type.hpp"
#include "benchmark_operation_symmetry.hpp"
#include "benchmark_ratnum_numeric_overhead.hpp"
#include "benchmark_bignum_fixnum_int64_t_comparison.hpp"

int main() {
  if (!BE_SILENT) STATE_WARMING_CONDITIONS

    std::cout << "Results will be printed at the end of all benchmarking." << std::endl << std::endl;

  std::ostringstream results;

  if (PERFORM_FIXNUM_BIGNUM_INT64_T_COMPARISON_BENCHMARKS) {
    add_results_fixnum_bignum_delineation(results);
  }

  if (PERFORM_RATNUM_NUMERIC_OVERHEAD_BENCHMARK) {
    add_result_ratnum_numeric_overhead(results);
  }

  if (PERFORM_OPERATION_SYMMETRY_BENCHMARKS) {
    add_results_operation_symmetry(results);
  }

  if (PERFORM_PERFORMANCE_PER_OPERAND_BENCHMARKS) {
    add_results_performance_per_operation_and_operand_type(results);
  }

  if (PERFORM_DOUBLING_BEHAVIOR_BENCHMARKS) {
    add_result_bignum_doubling_behavior(results);
    add_result_ratnum_doubling_behavior(results);
    add_result_exact_complexnum_doubling_behavior(results);
  }

  std::cout << std::endl << "RESULTS" << std::endl << std::endl << results.str();
  std::cout << std::endl << "END RESULTS" << std::endl << std::endl;

  return 0;
}

