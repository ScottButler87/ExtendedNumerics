#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_PERF_PER_OPERAND_TYPE_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_PERF_PER_OPERAND_TYPE_HPP_

#define PERF_PER_OPERAND_FIXNUM_SIZE 62
#define PERF_PER_OPERAND_BIGNUM_SIZE 350
#define PERF_PER_OPERAND_RATNUM_SIZE 117
#define ADDITION_INPUT_SIZE_MULTIPLIER 1
#define SUBTRACTION_INPUT_SIZE_MULTIPLIER 1
#define MULTIPLICATION_INPUT_SIZE_MULTIPLIER 1
#define DIVISION_INPUT_SIZE_MULTIPLIER 1

#define OPERAND_COMPARISON_OPERATION(BINARY_OP, OTHER_TYPE) \
operand_under_test BINARY_OP OTHER_TYPE##_operand

#define GENERATE_OPERAND_COMPARISON_DESCRIPTION(OPERAND_UNDER_TEST_TYPE, OTHER_TYPE, PRIMITIVE_OPERATION_NAME) \
std::stringstream OPERATION_DESCRIPTION_NAME(OPERAND_UNDER_TEST_TYPE, OTHER_TYPE, PRIMITIVE_OPERATION_NAME);\
OPERATION_DESCRIPTION_NAME(OPERAND_UNDER_TEST_TYPE, OTHER_TYPE, PRIMITIVE_OPERATION_NAME) << XSTR(PRIMITIVE_OPERATION_NAME) << " of " << \
XSTR(OPERAND_UNDER_TEST_TYPE) << " and " << XSTR(OTHER_TYPE) << " ";

#define OPERATION_DESCRIPTION_NAME(OPERAND_UNDER_TEST_TYPE, OTHER_TYPE, PRIMITIVE_OPERATION_NAME) \
OPERAND_UNDER_TEST_TYPE##_##OTHER_TYPE##_##PRIMITIVE_OPERATION_NAME##_description

#define ADD_RESULT_PERF_PER_OPERAND_TYPE(BINARY_OP, OPERATION_NAME, TEST_OPERAND_TYPE,\
OPERATION_OPERAND_SIZE_MULTIPLIER, OPERAND_SIZE, BIGNUM_SIZE, RATIONAL_SIZE, RESULTS_OSTREAM)\
{\
  Numeric operand_under_test = random_##TEST_OPERAND_TYPE(OPERAND_SIZE);\
  Numeric fixnum_operand = random_fixnum(PERF_PER_OPERAND_FIXNUM_SIZE);\
  Numeric bignum_operand = random_bignum(BIGNUM_SIZE);\
  Numeric ratnum_operand = random_ratnum(RATIONAL_SIZE);\
  Numeric exact_complexnum_operand = random_exact_complexnum(RATIONAL_SIZE);\
  Numeric inexact_complexnum_operand = random_inexact_complexnum();\
  \
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(TEST_OPERAND_TYPE, fixnum, OPERATION_NAME)\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(TEST_OPERAND_TYPE, bignum, OPERATION_NAME)\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(TEST_OPERAND_TYPE, ratnum, OPERATION_NAME)\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(TEST_OPERAND_TYPE, exact_complexnum, OPERATION_NAME)\
  GENERATE_OPERAND_COMPARISON_DESCRIPTION(TEST_OPERAND_TYPE, inexact_complexnum, OPERATION_NAME)\
  {\
    /* PROVIDES |=> time_sum (total runtime) and avg_time (time per full iteration) */ \
    WARM_AND_TIME_BENCHMARK_OPERATION(FAST_OP_LOOPS_PER_SAMPLE,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, fixnum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, fixnum),\
                                      OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, fixnum, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, fixnum, OPERATION_NAME).str()\
                              << " timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl << std::endl;\
  }\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(FAST_OP_LOOPS_PER_SAMPLE,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, bignum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, bignum),\
                                      OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, bignum, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, bignum, OPERATION_NAME).str()\
                              << " timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl << std::endl;\
  }\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(SLOW_OP_LOOPS_PER_SAMPLE,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, ratnum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, ratnum),\
                                      OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, ratnum, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, ratnum, OPERATION_NAME).str()\
                              << " timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl << std::endl;\
  }\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(SLOW_OP_LOOPS_PER_SAMPLE,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, exact_complexnum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, exact_complexnum),\
                                      OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, exact_complexnum, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, exact_complexnum, OPERATION_NAME).str()\
                              << " timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl << std::endl;\
  }\
  {\
    WARM_AND_TIME_BENCHMARK_OPERATION(MEDIUM_OP_LOOPS_PER_SAMPLE,\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, inexact_complexnum),\
                                      OPERAND_COMPARISON_OPERATION(BINARY_OP, inexact_complexnum),\
                                      OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, inexact_complexnum, OPERATION_NAME).str(),\
                                      BE_VERBOSE)\
    if (!BE_SILENT) std::cout << OPERATION_DESCRIPTION_NAME(TEST_OPERAND_TYPE, inexact_complexnum, OPERATION_NAME).str()\
                              << "timing took " << IN_LARGE_TIME_UNITS(time_sum) << " " << XSTR(LARGE_TIME_UNITS)\
                              << " beyond warming." << std::endl << std::endl;\
  }\
}

void add_result_fixnum_performance_per_operand_type(std::ostream &results) {
  ADD_RESULT_PERF_PER_OPERAND_TYPE(+, Addition, fixnum, ADDITION_INPUT_SIZE_MULTIPLIER, PERF_PER_OPERAND_FIXNUM_SIZE,
      PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(-, Subtraction, fixnum, SUBTRACTION_INPUT_SIZE_MULTIPLIER, PERF_PER_OPERAND_FIXNUM_SIZE,
      PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(*, Multiplication, fixnum, MULTIPLICATION_INPUT_SIZE_MULTIPLIER, PERF_PER_OPERAND_FIXNUM_SIZE,
      PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(/, Division, fixnum, DIVISION_INPUT_SIZE_MULTIPLIER, PERF_PER_OPERAND_FIXNUM_SIZE,
      PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
}

void add_result_bignum_performance_per_operand_type(std::ostream &results) {
  ADD_RESULT_PERF_PER_OPERAND_TYPE(+, addition, bignum, ADDITION_INPUT_SIZE_MULTIPLIER,
      PERF_PER_OPERAND_BIGNUM_SIZE * ADDITION_INPUT_SIZE_MULTIPLIER,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(-, subtraction, bignum, SUBTRACTION_INPUT_SIZE_MULTIPLIER,
                                   PERF_PER_OPERAND_BIGNUM_SIZE * SUBTRACTION_INPUT_SIZE_MULTIPLIER,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(*, multiplication, bignum, MULTIPLICATION_INPUT_SIZE_MULTIPLIER,
                                   PERF_PER_OPERAND_BIGNUM_SIZE * MULTIPLICATION_INPUT_SIZE_MULTIPLIER,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(/, division, bignum, DIVISION_INPUT_SIZE_MULTIPLIER,
                                   PERF_PER_OPERAND_BIGNUM_SIZE * DIVISION_INPUT_SIZE_MULTIPLIER,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
}

void add_result_ratnum_performance_per_operand_type(std::ostream &results) {
  ADD_RESULT_PERF_PER_OPERAND_TYPE(+, addition, ratnum, ADDITION_INPUT_SIZE_MULTIPLIER,
                                   ADDITION_INPUT_SIZE_MULTIPLIER * PERF_PER_OPERAND_RATNUM_SIZE,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(-, subtraction, ratnum, SUBTRACTION_INPUT_SIZE_MULTIPLIER,
                                   SUBTRACTION_INPUT_SIZE_MULTIPLIER * PERF_PER_OPERAND_RATNUM_SIZE,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(*, multiplication, ratnum, MULTIPLICATION_INPUT_SIZE_MULTIPLIER,
                                   MULTIPLICATION_INPUT_SIZE_MULTIPLIER * PERF_PER_OPERAND_RATNUM_SIZE,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(/, division, ratnum, DIVISION_INPUT_SIZE_MULTIPLIER,
                                   DIVISION_INPUT_SIZE_MULTIPLIER * PERF_PER_OPERAND_RATNUM_SIZE,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
}

void add_result_exact_complexnum_performance_per_operand_type(std::ostream &results) {
  ADD_RESULT_PERF_PER_OPERAND_TYPE(+, addition, exact_complexnum, ADDITION_INPUT_SIZE_MULTIPLIER,
                                   ADDITION_INPUT_SIZE_MULTIPLIER * PERF_PER_OPERAND_RATNUM_SIZE,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(-, subtraction, exact_complexnum, SUBTRACTION_INPUT_SIZE_MULTIPLIER,
                                   SUBTRACTION_INPUT_SIZE_MULTIPLIER * PERF_PER_OPERAND_RATNUM_SIZE,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(*, multiplication, exact_complexnum, MULTIPLICATION_INPUT_SIZE_MULTIPLIER,
                                   MULTIPLICATION_INPUT_SIZE_MULTIPLIER * PERF_PER_OPERAND_RATNUM_SIZE,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(/, division, exact_complexnum, DIVISION_INPUT_SIZE_MULTIPLIER,
                                   DIVISION_INPUT_SIZE_MULTIPLIER * PERF_PER_OPERAND_RATNUM_SIZE,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
}

void add_result_inexact_complexnum_performance_per_operand_type(std::ostream &results) {
  ADD_RESULT_PERF_PER_OPERAND_TYPE(+, addition, inexact_complexnum, ADDITION_INPUT_SIZE_MULTIPLIER,,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(-, subtraction, inexact_complexnum, SUBTRACTION_INPUT_SIZE_MULTIPLIER,,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(*, multiplication, inexact_complexnum, MULTIPLICATION_INPUT_SIZE_MULTIPLIER,,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
  ADD_RESULT_PERF_PER_OPERAND_TYPE(/, division, inexact_complexnum, DIVISION_INPUT_SIZE_MULTIPLIER,,
                                   PERF_PER_OPERAND_BIGNUM_SIZE, PERF_PER_OPERAND_RATNUM_SIZE, results)
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_BENCHMARK_PERF_PER_OPERAND_TYPE_HPP_
