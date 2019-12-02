#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_RATNUM_OPS_HPP_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_RATNUM_OPS_HPP_HPP_

#include "doubling_behavior.hpp"

/* USAGE |=> Passed into ADD_RESULT_DOUBLING_BEHAVIOR as the description generator for ratnum operations */
#define GENERATE_RATNUM_OP_DESCRIPTION(DESCRIPTION_NAME, OPERATION_NAME, OPERAND_BIT_SIZE) \
std::stringstream DESCRIPTION_NAME;\
DESCRIPTION_NAME << XSTR(OPERATION_NAME) << " of two random " << OPERAND_BIT_SIZE << \
" bit numbers "; \
//  << small_ratnum_left << std::endl << small_ratnum_right << std::endl; (add MSChunk ... LSChunk)

void add_result_ratnum_addition_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, ratnum, +, Addition,,
                               GENERATE_RATNUM_OP_DESCRIPTION, ADDITION_SUBTRACTION_DIVISION_BASE_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_ratnum_subtraction_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, ratnum, -, Subtraction,,
                               GENERATE_RATNUM_OP_DESCRIPTION, ADDITION_SUBTRACTION_DIVISION_BASE_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_ratnum_multiplication_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, ratnum, *, Multiplication,,
                               GENERATE_RATNUM_OP_DESCRIPTION, MULTIPLICATION_BASE_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_ratnum_division_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, ratnum, /, Division,,
                               GENERATE_RATNUM_OP_DESCRIPTION, ADDITION_SUBTRACTION_DIVISION_BASE_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_RATNUM_OPS_HPP_HPP_