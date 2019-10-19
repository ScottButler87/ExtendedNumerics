//
// Created by scott on 10/13/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_NUMERICOPERATIONS_HPP_
#define WASMEXTENDEDNUMERICS_SRC_NUMERICOPERATIONS_HPP_
//
// Created by scott on 9/21/19.
//

#ifndef NUMERIC_OPERATIONS_H_
#define NUMERIC_OPERATIONS_H_
#include <sstream>
#define VIRTUAL_NUM_OP(OP_NAME, TYPE_NAME) virtual std::unique_ptr<const NumericOperations> OP_NAME ## TYPE_NAME(std::shared_ptr<const NumericOperations> right) const = 0;
#define VIRTUAL_NUM_OP_FOR_ALL_TYPES(OP_NAME)                                                          \
  virtual std::unique_ptr<const NumericOperations> OP_NAME ## Fixnum(int64_t fixnum) const = 0;        \
  VIRTUAL_NUM_OP(OP_NAME, Bignum)                                                                      \
  VIRTUAL_NUM_OP(OP_NAME, Ratnum)                                                                      \
  VIRTUAL_NUM_OP(OP_NAME, InexactComplexnum)                                                           \
  VIRTUAL_NUM_OP(OP_NAME, ExactComplexnum)                                                             \
  VIRTUAL_NUM_OP(OP_NAME, Flonum)

#define NUM_OP_DECL(OP_SYMBOL, RETURN_TYPE, ARG_TYPE)\
std::unique_ptr<const RETURN_TYPE> operator OP_SYMBOL(const ARG_TYPE &right) const

#define NUM_COMP_DECL(OP_SYMBOL, ARG_TYPE)\
bool operator OP_SYMBOL(const ARG_TYPE &right) const

#endif // NUMERIC_OPERATIONS_H_

#endif //WASMEXTENDEDNUMERICS_SRC_NUMERICOPERATIONS_HPP_
