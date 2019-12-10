#include "benchmark_bignum_fixnum_int64_t_comparison.hpp"

int main () {
  if (!BE_SILENT) STATE_WARMING_CONDITIONS

  std::cout << "Results will be printed at the end of all benchmarking." << std::endl << std::endl;

  std::ostringstream results("");

  //TODO add results to string stream after running benchmarks above
  add_results_fixnum_bignum_delineation(results);

  std::cout << std::endl << "RESULTS" << std::endl << std::endl << results.str();

  return 0;
}