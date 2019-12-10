#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_DOUBLING_BEHAVIOR_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_DOUBLING_BEHAVIOR_HPP_

#include <iostream>
#include <iomanip>
#include "benchmark_settings_and_defs.hpp"
#include "time_benchmark_operation.hpp"
#include "random_numeric_generators.hpp"
#include "../src/Numeric.hpp"

// eases space constraints
#define IBCS DOUBLING_BEHAVIOR_INPUT_BIT_COLUMN_SIZE
#define TPOCS TIME_PER_OPERATION_COLUMN_SIZE
#define RCS DOUBLING_BEHAVIOR_RATIO_COLUMN_SIZE

#define DOUBLING_BEHAVIOR_HEADER(OPERAND_TYPE, OPERATION_NAME, OSTREAM) \
OSTREAM << std::right\
        << "Doubling behavior for " << XSTR(OPERAND_TYPE) << " " << XSTR_LOWER(OPERATION_NAME) << ":" << std::endl\
        << std::endl\
        << std::setw(IBCS) << "Input bit size" << std::setw(TPOCS) << "Time per operation"\
        << std::setw(RCS) << "Ratio" << std::endl;

#define DOUBLING_BEHAVIOR_FIRST_ROW(INPUT_BIT_SIZE, TIME_PER_OPERATION, OSTREAM) \
OSTREAM << std::right\
        << std::setw(IBCS) << INPUT_BIT_SIZE << std::setw(TPOCS) << TIME_PER_OPERATION_TO_STRING(TIME_PER_OPERATION)\
        << std::endl;

#define DOUBLING_BEHAVIOR_ADDITIONAL_ROW(INPUT_BIT_SIZE, TIME_PER_OPERATION, LAST_TIME_PER_OPERATION, OSTREAM) \
OSTREAM << std::right\
        << std::setw(IBCS) << INPUT_BIT_SIZE << std::setw(TPOCS) << TIME_PER_OPERATION_TO_STRING(TIME_PER_OPERATION)\
        << std::setw(RCS) << std::setprecision(DOUBLING_BEHAVIOR_RATIO_SIG_FIGS) << std::fixed\
        << TIME_PER_OPERATION / LAST_TIME_PER_OPERATION << std::endl\
        << std::defaultfloat << std::setprecision(6);

#define ADD_RESULT_DOUBLING_BEHAVIOR(LOOPS_PER_SAMPLE, OPERAND_TYPE,\
      BINARY_OP, OPERATION_NAME, RANDOM_FUNCTION_SUFFIX, DESCRIPTION_GENERATOR, BASE_BIT_SIZE, MAKE_VERBOSE, RESULTS_OSTREAM) \
{\
  if (!BE_SILENT) std::cout << "Calculating doubling behavior for " << XSTR(OPERAND_TYPE)\
    << " " << XSTR_LOWER(OPERATION_NAME) << " with " << BASE_BIT_SIZE << " bit inputs to start and " << LOOPS_PER_SAMPLE\
    << " iterations per run." << std::endl << std::endl;\
  Numeric warming_left_8x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 8);\
  Numeric warming_right_8x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 8);\
  Numeric OPERAND_TYPE##_left_base = random_##OPERAND_TYPE ##RANDOM_FUNCTION_SUFFIX(BASE_BIT_SIZE);\
  Numeric OPERAND_TYPE##_right_base = random_##OPERAND_TYPE(BASE_BIT_SIZE);\
  Numeric OPERAND_TYPE##_left_2x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 2);\
  Numeric OPERAND_TYPE##_right_2x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 2);\
  Numeric OPERAND_TYPE##_left_4x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 4);\
  Numeric OPERAND_TYPE##_right_4x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 4);\
  Numeric OPERAND_TYPE##_left_8x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 8);\
  Numeric OPERAND_TYPE##_right_8x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 8);\
  Numeric OPERAND_TYPE##_left_16x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 16);\
  Numeric OPERAND_TYPE##_right_16x = random_##OPERAND_TYPE(BASE_BIT_SIZE * 16);\
  DESCRIPTION_GENERATOR(description_base, OPERATION_NAME, BASE_BIT_SIZE)\
  DESCRIPTION_GENERATOR(description_2x, OPERATION_NAME, BASE_BIT_SIZE * 2)\
  DESCRIPTION_GENERATOR(description_4x, OPERATION_NAME, BASE_BIT_SIZE * 4)\
  DESCRIPTION_GENERATOR(description_8x, OPERATION_NAME, BASE_BIT_SIZE * 8)\
  DESCRIPTION_GENERATOR(description_16x, OPERATION_NAME, BASE_BIT_SIZE * 16)\
  std::chrono::TIME_UNITS avg_time_base;\
  std::chrono::TIME_UNITS avg_time_2x;\
  std::chrono::TIME_UNITS avg_time_4x;\
  std::chrono::TIME_UNITS avg_time_8x;\
  std::chrono::TIME_UNITS avg_time_16x;\
  std::chrono::TIME_UNITS total_runtime(0);\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE, warming_left_8x BINARY_OP warming_right_8x,\
        OPERAND_TYPE##_left_16x BINARY_OP OPERAND_TYPE##_right_16x,\
                             description_16x.str(), MAKE_VERBOSE)\
    avg_time_16x = avg_time;\
    total_runtime += time_sum;\
  }\
  if (!BE_SILENT) std::cout << "Finished timing 16x base bit size input." << std::endl;\
  {\
    /* PROVIDES |=> calculates time_sum (total runtime) and avg_time (time per full iteration) */ \
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE, OPERAND_TYPE##_left_base BINARY_OP OPERAND_TYPE##_right_base,\
                             description_base.str(), MAKE_VERBOSE)\
    avg_time_base = avg_time;\
    total_runtime += time_sum;\
  }\
  if (!BE_SILENT) std::cout << "Finished timing base bit size input." << std::endl;\
  {\
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE,  OPERAND_TYPE##_left_2x BINARY_OP OPERAND_TYPE##_right_2x,\
                             description_2x.str(), MAKE_VERBOSE)\
    avg_time_2x = avg_time;\
    total_runtime += time_sum;\
  }\
  if (!BE_SILENT) std::cout << "Finished timing 2x base bit size input." << std::endl;\
  {\
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE, OPERAND_TYPE##_left_4x BINARY_OP OPERAND_TYPE##_right_4x,\
                             description_4x.str(), MAKE_VERBOSE)\
    avg_time_4x = avg_time;\
    total_runtime += time_sum;\
  }\
  if (!BE_SILENT) std::cout << "Finished timing 4x base bit size input." << std::endl;\
  {\
    TIME_BENCHMARK_OPERATION(LOOPS_PER_SAMPLE, OPERAND_TYPE##_left_8x BINARY_OP OPERAND_TYPE##_right_8x,\
                             description_8x.str(), MAKE_VERBOSE)\
    avg_time_8x = avg_time;\
    total_runtime += time_sum;\
  }\
  if (!BE_SILENT) std::cout << "Finished timing 8x base bit size input." << std::endl\
    << "Total operation runtime not including warming was " << IN_LARGE_TIME_UNITS(total_runtime)\
    << " " << XSTR(LARGE_TIME_UNITS) << "." << std::endl << std::endl << std::flush;\
  double per_op_time_base = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_base, LOOPS_PER_SAMPLE);\
  double per_op_time_2x = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_2x, LOOPS_PER_SAMPLE);\
  double per_op_time_4x = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_4x, LOOPS_PER_SAMPLE);\
  double per_op_time_8x = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_8x, LOOPS_PER_SAMPLE);\
  double per_op_time_16x = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_16x, LOOPS_PER_SAMPLE);\
  DOUBLING_BEHAVIOR_HEADER(OPERAND_TYPE, OPERATION_NAME, RESULTS_OSTREAM)\
  DOUBLING_BEHAVIOR_FIRST_ROW(BASE_BIT_SIZE, per_op_time_base, RESULTS_OSTREAM)\
  DOUBLING_BEHAVIOR_ADDITIONAL_ROW(BASE_BIT_SIZE * 2, per_op_time_2x, per_op_time_base, RESULTS_OSTREAM)\
  DOUBLING_BEHAVIOR_ADDITIONAL_ROW(BASE_BIT_SIZE * 4, per_op_time_4x, per_op_time_2x, RESULTS_OSTREAM)\
  DOUBLING_BEHAVIOR_ADDITIONAL_ROW(BASE_BIT_SIZE * 8, per_op_time_8x, per_op_time_4x, RESULTS_OSTREAM)\
  DOUBLING_BEHAVIOR_ADDITIONAL_ROW(BASE_BIT_SIZE * 16, per_op_time_16x, per_op_time_8x, RESULTS_OSTREAM)\
  RESULTS_OSTREAM << std::endl << std::endl;\
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_DOUBLING_BEHAVIOR_HPP_
