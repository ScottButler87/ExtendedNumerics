#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_RATNUM_NUMERIC_OVERHEAD_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_RATNUM_NUMERIC_OVERHEAD_HPP_

#include "../src/ExtendedNumerics.hpp"
#include "random_numeric_generators.hpp"
#include "time_benchmark_operation.hpp"

#define RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS 5000
#define RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND 1000

void add_result_ratnum_numeric_overhead(std::ostream &results) {
  cpp_rational ratnum_internal = random_cpp_rational(RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND);
  cpp_rational ratnum_internal2 = random_cpp_rational(RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND);
  Numeric numeric_ratnum((cpp_rational(ratnum_internal)));
  Numeric numeric_ratnum2((cpp_rational (ratnum_internal2)));
  cpp_rational ratnums_summed = ratnum_internal + ratnum_internal2;
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS,
                                      Numeric(cpp_rational(ratnums_summed)) , Numeric(cpp_rational(ratnums_summed)),
                                      "Numeric(cpp_rational(ratnums_summed))", BE_VERBOSE);
  }
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS,
                                      Numeric(ratnum_internal + ratnum_internal2), Numeric(ratnum_internal + ratnum_internal2),
                                      "Numeric(ratnum_internal + ratnum_internal2)", BE_VERBOSE);
  }
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS,
                                      Numeric(numeric_ratnum + numeric_ratnum2), Numeric(numeric_ratnum + numeric_ratnum2),
                                      "Numeric(numeric_ratnum + numeric_ratnum2)", BE_VERBOSE);
  }
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_RATNUM_NUMERIC_OVERHEAD_HPP_
