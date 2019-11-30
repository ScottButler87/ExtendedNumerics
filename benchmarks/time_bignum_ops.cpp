#include "random_numeric_generators.hpp"
#include "benchmark_settings_and_defs.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>

/* DEPENDENCY |=> DEMO_DOUBLING_BEHAVIOR depends on this to generate descriptions */
#define GENERATE_BIGNUM_OP_DESCRIPTION(DESCRIPTION_NAME, OPERATION_NAME, OPERAND_BIT_SIZE) \
std::stringstream DESCRIPTION_NAME;\
DESCRIPTION_NAME << XSTR(OPERATION_NAME) << " of two random " << OPERAND_BIT_SIZE << \
" bit numbers "; \
//  << small_bignum_left << std::endl << small_bignum_right << std::endl; (add MSChunk ... LSChunk)

void demo_bignum_addition_doubling_behavior() {
  DEMO_DOUBLING_BEHAVIOR(MEDIUM_OP_LOOPS_PER_SAMPLE, bignum, +, Addition,
      GENERATE_BIGNUM_OP_DESCRIPTION, ADDITION_SUBTRACTION_BASE_BIT_SIZE, false)
}

int main() {
  STATE_WARMING_CONDITIONS

  demo_bignum_addition_doubling_behavior();
  // add
  // sub
  // mult
  // div
}

