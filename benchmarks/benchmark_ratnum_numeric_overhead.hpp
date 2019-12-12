#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_RATNUM_NUMERIC_OVERHEAD_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_RATNUM_NUMERIC_OVERHEAD_HPP_

#include "../src/Numeric.hpp"
#include "random_numeric_generators.hpp"
#include "time_benchmark_operation.hpp"
#include "_benchmark_settings_and_defs.hpp"
#include <chrono>

#define RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS 5000
#define RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND 77

void add_result_ratnum_numeric_overhead(std::ostream &results) {
  cpp_rational ratnum_internal = random_cpp_rational(RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND);
  cpp_rational ratnum_internal2 = random_cpp_rational(RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND);
  Numeric numeric_ratnum((cpp_rational(ratnum_internal)));
  Numeric numeric_ratnum2((cpp_rational (ratnum_internal2)));
  cpp_rational ratnums_summed = ratnum_internal + ratnum_internal2;
  if (!BE_SILENT) {
    std::cout << "Timing ratnum numeric overhead. Comparison loops: " << RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS << std::endl
              << "Ratnum numeric overhead bits per operation: " << RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND << std::endl << std::endl;
  }
  results << std::endl << "Ratnum numeric overhead:" << std::endl << std::endl
          << "LEFT_OPERAND_TYPE,RIGHT_OPERAND_TYPE,OPERATION,BITS_PER_OPERAND,COMPARISON_LOOPS,AVERAGE_TIME_PER_LOOP,TOTAL_TIME,TIME_UNITS"
          << std::endl;
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS,
                                      Numeric(cpp_rational(ratnums_summed)) , Numeric(cpp_rational(ratnums_summed)),
                                      "Numeric(cpp_rational(ratnums_summed))", BE_VERBOSE)
    results << "ratnum,none,construction," << RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND << "," << RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS << ","
            << std::chrono::duration_cast<std::chrono::TIME_UNITS>(avg_time).count() << "," << std::chrono::duration_cast<std::chrono::TIME_UNITS>(time_sum).count()
            << "," << XSTR(TIME_UNITS_ABBREVIATION) << std::endl;
  }
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS,
                                      Numeric(ratnum_internal + ratnum_internal2), Numeric(ratnum_internal + ratnum_internal2),
                                      "Numeric(ratnum_internal + ratnum_internal2)", BE_VERBOSE)
    results << "cpp_rational,cpp_rational,addition," << RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND << "," << RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS << ","
            << std::chrono::duration_cast<std::chrono::TIME_UNITS>(avg_time).count() << "," << std::chrono::duration_cast<std::chrono::TIME_UNITS>(time_sum).count()
            << "," << XSTR(TIME_UNITS_ABBREVIATION) << std::endl;
  }
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS,
                                      Numeric(numeric_ratnum + numeric_ratnum2), Numeric(numeric_ratnum + numeric_ratnum2),
                                      "Numeric(numeric_ratnum + numeric_ratnum2)", BE_VERBOSE)
    results << "ratnum,ratnum,addition," << RATNUM_NUMERIC_OVERHEAD_BITS_PER_OPERAND << "," << RATNUM_NUMERIC_OVERHEAD_COMPARISON_LOOPS << ","
            << std::chrono::duration_cast<std::chrono::TIME_UNITS>(avg_time).count() << "," << std::chrono::duration_cast<std::chrono::TIME_UNITS>(time_sum).count()
            << "," << XSTR(TIME_UNITS_ABBREVIATION) << std::endl;
  }
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_RATNUM_NUMERIC_OVERHEAD_HPP_
