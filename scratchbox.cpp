

#include "src/ExtendedNumerics.hpp"
#include "benchmarks/random_numeric_generators.hpp"
#include "benchmarks/time_benchmark_operation.hpp"
int main() {
  Numeric rat = random_ratnum(350);
  Numeric big = random_bignum(2080);
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(10000, rat + big, rat + big, "rat + big", true);
  }
  {
    WARM_AND_TIME_BENCHMARK_OPERATION(10000, big + rat, big + rat, "big + rat", true);
  }
}