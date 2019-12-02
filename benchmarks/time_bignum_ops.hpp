#ifndef WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_BIGNUM_OPS_HPP_
#define WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_BIGNUM_OPS_HPP_

#include "doubling_behavior.hpp"

/* USAGE |=> Passed into ADD_RESULT_DOUBLING_BEHAVIOR as the description generator for bignum operations */
#define GENERATE_BIGNUM_OP_DESCRIPTION(DESCRIPTION_NAME, OPERATION_NAME, OPERAND_BIT_SIZE) \
std::stringstream DESCRIPTION_NAME;\
DESCRIPTION_NAME << XSTR(OPERATION_NAME) << " of two random " << OPERAND_BIT_SIZE << \
" bit numbers "; \
//  << small_bignum_left << std::endl << small_bignum_right << std::endl; (add MSChunk ... LSChunk)

void add_result_bignum_addition_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, bignum, +, Addition,,
                               GENERATE_BIGNUM_OP_DESCRIPTION, ADDITION_SUBTRACTION_DIVISION_BASE_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_bignum_subtraction_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, bignum, -, Subtraction,,
                               GENERATE_BIGNUM_OP_DESCRIPTION, ADDITION_SUBTRACTION_DIVISION_BASE_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_bignum_multiplication_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, bignum, *, Multiplication,,
                               GENERATE_BIGNUM_OP_DESCRIPTION, MULTIPLICATION_BASE_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

void add_result_bignum_division_doubling_behavior(std::ostream &results_stream) {
  ADD_RESULT_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, bignum, /, Division,,
                               GENERATE_BIGNUM_OP_DESCRIPTION, ADDITION_SUBTRACTION_DIVISION_BASE_BIT_SIZE, BE_VERBOSE,
                               results_stream)
}

#endif //WASMEXTENDEDNUMERICS_BENCHMARKS_TIME_BIGNUM_OPS_HPP_
