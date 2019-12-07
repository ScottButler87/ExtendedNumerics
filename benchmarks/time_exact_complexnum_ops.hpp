#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_EXACT_COMPLEXNUM_OPS_HPP_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_EXACT_COMPLEXNUM_OPS_HPP_HPP_

#include "doubling_behavior.hpp"
#include "benchmark_settings_and_defs.hpp"

/* USAGE |=> Passed into ADD_RESULT_DOUBLING_BEHAVIOR as the description generator for exact_complexnum operations */
#define GENERATE_EXACT_COMPLEXNUM_OP_DESCRIPTION(DESCRIPTION_NAME, OPERATION_NAME, OPERAND_BIT_SIZE) \
std::stringstream DESCRIPTION_NAME;\
DESCRIPTION_NAME << XSTR(OPERATION_NAME) << " of two random " << OPERAND_BIT_SIZE << \
" bit numbers "; \
//  << small_exact_complexnum_left << std::endl << small_exact_complexnum_right << std::endl; (add MSChunk ... LSChunk)

void add_result_exact_complexnum_addition_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, exact_complexnum, +, Addition,,
                               GENERATE_EXACT_COMPLEXNUM_OP_DESCRIPTION, RATIONAL_NUMBER_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_exact_complexnum_subtraction_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, exact_complexnum, -, Subtraction,,
                               GENERATE_EXACT_COMPLEXNUM_OP_DESCRIPTION, RATIONAL_NUMBER_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_exact_complexnum_multiplication_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(SLOW_OP_LOOPS_PER_SAMPLE, exact_complexnum, *, Multiplication,,
                               GENERATE_EXACT_COMPLEXNUM_OP_DESCRIPTION, RATIONAL_NUMBER_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_exact_complexnum_division_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(SLOW_OP_LOOPS_PER_SAMPLE, exact_complexnum, /, Division,,
                               GENERATE_EXACT_COMPLEXNUM_OP_DESCRIPTION, RATIONAL_NUMBER_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_exact_complexnum_doubling_behavior(std::ostream &results_stream) {
  add_result_exact_complexnum_addition_doubling_behavior(results_stream);
  add_result_exact_complexnum_subtraction_doubling_behavior(results_stream);
  add_result_exact_complexnum_multiplication_doubling_behavior(results_stream);
  add_result_exact_complexnum_division_doubling_behavior(results_stream);
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_EXACT_COMPLEXNUM_OPS_HPP_HPP_
