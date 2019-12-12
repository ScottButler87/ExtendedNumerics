#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_PERF_PER_OPERAND_TYPE_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_PERF_PER_OPERAND_TYPE_HPP_

#include "_benchmark_settings_and_defs.hpp"

// eases space constraints
#define ONCS PERF_PER_OPERAND_OPERATION_COLUMN_SIZE
#define OCS PERF_PER_OPERAND_OPERAND_COLUMN_SIZE
#ifndef TPOCS
  #define TPOCS TIME_PER_OPERATION_COLUMN_SIZE
#endif


#define OPERAND_COMPARISON_OPERATION(BINARY_OP, OTHER_TYPE) \
OTHER_TYPE##_operand BINARY_OP operand_under_test 

#define GENERATE_OPERAND_COMPARISON_DESCRIPTION(OTHER_TYPE, OPERAND_UNDER_TEST_TYPE, PRIMITIVE_OPERATION_NAME) \
std::stringstream OPERATION_DESCRIPTION_NAME(OTHER_TYPE, OPERAND_UNDER_TEST_TYPE, PRIMITIVE_OPERATION_NAME);\
OPERATION_DESCRIPTION_NAME(OTHER_TYPE, OPERAND_UNDER_TEST_TYPE, PRIMITIVE_OPERATION_NAME) << XSTR(PRIMITIVE_OPERATION_NAME) << " of " << \
XSTR(OTHER_TYPE) << " and " << XSTR(OPERAND_UNDER_TEST_TYPE) << " ";

#define OPERATION_DESCRIPTION_NAME(OTHER_TYPE, OPERAND_UNDER_TEST_TYPE, PRIMITIVE_OPERATION_NAME) \
OTHER_TYPE##_##OPERAND_UNDER_TEST_TYPE##_##PRIMITIVE_OPERATION_NAME##_description

#define PERFORMANCE_PER_OPERAND_HEADER(RESULTS_OSTREAM) \
RESULTS_OSTREAM << std::setw(ONCS) << "OPERATION" << std::setw(OCS) << "Left Operand" << std::setw(OCS)\
<< "Right Operand" << std::setw(TPOCS) << "Time per operation" << std::endl;

#define PERFORMANCE_PER_OPERAND_OPERATION_HEADER_LINE(RESULTS_OSTREAM, OPERATION_NAME, LEFT_OPERAND_TYPE,\
RIGHT_OPERAND_TYPE, TIME_PER_OPERATION)\
RESULTS_OSTREAM << std::setw(ONCS) << XSTR(OPERATION_NAME)\
                << std::setw(OCS) << XSTR_LOWER(LEFT_OPERAND_TYPE)\
                << std::setw(OCS) << XSTR_LOWER(RIGHT_OPERAND_TYPE)\
                << std::setw(TPOCS) << TIME_PER_OPERATION_TO_STRING(TIME_PER_OPERATION)\
                << std::endl;

#define PERFORMANCE_PER_OPERAND_OPERATION_ADDITIONAL_LINE(RESULTS_OSTREAM, LEFT_OPERAND_TYPE,\
RIGHT_OPERAND_TYPE, TIME_PER_OPERATION)\
RESULTS_OSTREAM << std::setw(ONCS + OCS) << XSTR_LOWER(LEFT_OPERAND_TYPE)\
                << std::setw(OCS) << XSTR_LOWER(RIGHT_OPERAND_TYPE)\
                << std::setw(TPOCS) << TIME_PER_OPERATION_TO_STRING(TIME_PER_OPERATION) << std::endl;

#define ADD_RESULT_PERF_PER_OPERAND_TYPE(LOOPS_PER_COMPARISON, BINARY_OP, OPERATION_NAME,\
TEST_OPERAND_TYPE, OPERAND_SIZE, RESULTS_OSTREAM)\
{\
  Numeric operand_under_test = random_##TEST_OPERAND_TYPE(OPERAND_SIZE);\
  Numeric fixnum_operand = random_fixnum(PERF_PER_OPERAND_FIXNUM_SIZE);\
  Numeric bignum_operand = OPERAND_SIZE == PERF_PER_OPERAND_RATNUM_SIZE ?\
      random_bignum(PERF_PER_OPERAND_RATNUM_SIZE) :\
      random_bignum(PERF_PER_OPERAND_BIGNUM_SIZE);\
  \
  Numeric ratnum_operand = random_ratnum(PERF_PER_OPERAND_RATNUM_SIZE);\
  Numeric exact_complexnum_operand = random_exact_complexnum(PERF_PER_OPERAND_RATNUM_SIZE);\
  Numeric inexact_complexnum_operand = random_inexact_complexnum(0);\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(fixnum, TEST_OPERAND_TYPE, OPERATION_NAME)\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(bignum, TEST_OPERAND_TYPE, OPERATION_NAME)\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(ratnum, TEST_OPERAND_TYPE, OPERATION_NAME)\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(exact_complexnum, TEST_OPERAND_TYPE, OPERATION_NAME)\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(inexact_complexnum, TEST_OPERAND_TYPE, OPERATION_NAME)\
  std::chrono::TIME_UNITS avg_time_fixnum;\
  std::chrono::TIME_UNITS avg_time_bignum;\
  std::chrono::TIME_UNITS avg_time_ratnum;\
  std::chrono::TIME_UNITS avg_time_exact_complexnum;\
  std::chrono::TIME_UNITS avg_time_inexact_complexnum;\
  std::chrono::TIME_UNITS total_runtime(0);\
  {\
    /* PROVIDES |=> time_sum (total runtime) and avg_time (time per full iteration) */ \
    WARM_AND_TIME_BENCHMARK_OPERATION(LOOPS_PER_COMPARISON,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, fixnum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, fixnum),\
                                      OPERATION_DESCRIPTION_NAME(fixnum, TEST_OPERAND_TYPE, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(fixnum, TEST_OPERAND_TYPE, OPERATION_NAME).str()\
                              << "timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl;\
    avg_time_fixnum = avg_time;\
    total_runtime += time_sum;\
  }\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(LOOPS_PER_COMPARISON,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, inexact_complexnum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, inexact_complexnum),\
                                      OPERATION_DESCRIPTION_NAME(inexact_complexnum, TEST_OPERAND_TYPE, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    avg_time_inexact_complexnum = avg_time;\
    total_runtime += time_sum;\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(inexact_complexnum, TEST_OPERAND_TYPE, OPERATION_NAME).str()\
                              << "timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl;\
  }\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(LOOPS_PER_COMPARISON,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, bignum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, bignum),\
                                      OPERATION_DESCRIPTION_NAME(bignum, TEST_OPERAND_TYPE, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(bignum, TEST_OPERAND_TYPE, OPERATION_NAME).str()\
                              << "timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl;\
    avg_time_bignum = avg_time;\
    total_runtime += time_sum;\
  }\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(LOOPS_PER_COMPARISON,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, ratnum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, ratnum),\
                                      OPERATION_DESCRIPTION_NAME(ratnum, TEST_OPERAND_TYPE, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(ratnum, TEST_OPERAND_TYPE, OPERATION_NAME).str()\
                              << "timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl;\
    avg_time_ratnum = avg_time;\
    total_runtime += time_sum;\
  }\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(LOOPS_PER_COMPARISON,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, exact_complexnum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, exact_complexnum),\
                                      OPERATION_DESCRIPTION_NAME(exact_complexnum, TEST_OPERAND_TYPE, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(exact_complexnum, TEST_OPERAND_TYPE, OPERATION_NAME).str()\
                              << "timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl;\
    avg_time_exact_complexnum = avg_time;\
    total_runtime += time_sum;\
  }\
  double per_op_time_fixnum = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_fixnum, LOOPS_PER_COMPARISON);\
  double per_op_time_inexact_complexnum = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_inexact_complexnum, LOOPS_PER_COMPARISON);\
  double per_op_time_bignum = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_bignum, LOOPS_PER_COMPARISON);\
  double per_op_time_ratnum = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_ratnum, LOOPS_PER_COMPARISON);\
  double per_op_time_exact_complexnum = AVG_TIME_TO_PER_OPERATION_TIME(avg_time_exact_complexnum, LOOPS_PER_COMPARISON);\
  PERFORMANCE_PER_OPERAND_OPERATION_HEADER_LINE(RESULTS_OSTREAM, OPERATION_NAME, fixnum,\
  TEST_OPERAND_TYPE, per_op_time_fixnum)\
  PERFORMANCE_PER_OPERAND_OPERATION_ADDITIONAL_LINE(RESULTS_OSTREAM, inexact_complexnum,\
  TEST_OPERAND_TYPE, per_op_time_inexact_complexnum)\
  PERFORMANCE_PER_OPERAND_OPERATION_ADDITIONAL_LINE(RESULTS_OSTREAM, bignum,\
  TEST_OPERAND_TYPE, per_op_time_bignum)\
  PERFORMANCE_PER_OPERAND_OPERATION_ADDITIONAL_LINE(RESULTS_OSTREAM, ratnum,\
  TEST_OPERAND_TYPE, per_op_time_ratnum)\
  PERFORMANCE_PER_OPERAND_OPERATION_ADDITIONAL_LINE(RESULTS_OSTREAM, exact_complexnum,\
  TEST_OPERAND_TYPE, per_op_time_exact_complexnum)\
  RESULTS_OSTREAM << std::endl;\
}

void add_result_fixnum_performance_per_operand_type(std::ostream &results) {
  if (!BE_SILENT) std::cout << "Beginning performance per operand calculations..." << std::endl << std::endl;
  results << "Fixnums: " << std::endl;
  PERFORMANCE_PER_OPERAND_HEADER(results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, +, Addition, fixnum,
                                   PERF_PER_OPERAND_FIXNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, -, Subtraction, fixnum,
                                   PERF_PER_OPERAND_FIXNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, *, Multiplication, fixnum,
                                   PERF_PER_OPERAND_FIXNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, /, Division, fixnum,
                                   PERF_PER_OPERAND_FIXNUM_SIZE, results)
  results << std::endl << std::endl;
}

void add_result_inexact_complexnum_performance_per_operand_type(std::ostream &results) {
  results << "Inexact Complexnums: " << std::endl;
  PERFORMANCE_PER_OPERAND_HEADER(results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, +, Addition, inexact_complexnum, 0,
                                   results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, -, Subtraction, inexact_complexnum, 0,
                                   results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, *, Multiplication, inexact_complexnum, 0,
                                   results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, /, Division, inexact_complexnum, 0,
                                   results)
  results << std::endl << std::endl;
}

void add_result_bignum_performance_per_operand_type(std::ostream &results) {
  results << "Bignums: " << std::endl;
  PERFORMANCE_PER_OPERAND_HEADER(results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, +, Addition, bignum,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, -, Subtraction, bignum,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, *, Multiplication, bignum,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, /, Division, bignum,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, results)
  results << std::endl << std::endl;
}

void add_result_ratnum_performance_per_operand_type(std::ostream &results) {
  results << "Ratnums: " << std::endl;
  PERFORMANCE_PER_OPERAND_HEADER(results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, +, Addition, ratnum,
                                   PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, -, Subtraction, ratnum,
                                   PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, *, Multiplication, ratnum,
                                   PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, /, Division, ratnum,
                                   PERF_PER_OPERAND_RATNUM_SIZE, results)
  results << std::endl << std::endl;
}

void add_result_exact_complexnum_performance_per_operand_type(std::ostream &results) {
  results << "Exact Complexnums: " << std::endl;
  PERFORMANCE_PER_OPERAND_HEADER(results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, +, Addition, exact_complexnum,
                                   PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(MEDIUM_OP_LOOPS_PER_SAMPLE, -, Subtraction, exact_complexnum,
                                   PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, *, Multiplication, exact_complexnum,
                                   PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(SLOW_OP_LOOPS_PER_SAMPLE, /, Division, exact_complexnum,
                                   PERF_PER_OPERAND_RATNUM_SIZE, results)
  results << std::endl << std::endl;
}

void add_results_performance_per_operation_and_operand_type(std::ostream &results) {
  results << "Performance Per Operand Type and Operation Comparisons:" << std::endl << std::endl;
  add_result_fixnum_performance_per_operand_type(results);
  add_result_inexact_complexnum_performance_per_operand_type(results);
  add_result_bignum_performance_per_operand_type(results);
  add_result_ratnum_performance_per_operand_type(results);
  add_result_exact_complexnum_performance_per_operand_type(results);
  results << std::endl;
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_PERF_PER_OPERAND_TYPE_HPP_
