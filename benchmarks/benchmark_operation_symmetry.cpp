#include "benchmark_operation_symmetry.hpp"

int main() {
  std::stringstream results;
  add_results_operation_symmetry(results);
  std::cout << results.str();
}
