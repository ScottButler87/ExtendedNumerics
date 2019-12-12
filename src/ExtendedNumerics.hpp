#ifndef WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_
#define WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_

#include "boost/multiprecision/cpp_int.hpp"
#include <cstdlib>

//TODO extend functionality: add more Numeric/cprimitive operation overloads

#ifndef FORCE_INLINE
#ifndef SWIGGING_EXTENSION
  #define FORCE_INLINE __attribute__((always_inline)) inline
#else
  #define FORCE_INLINE
#endif
#endif

#define ENABLE_GMP 0
#define PRINT_DEBUG 1

// switch to GMP backend for cpp_ints
#if ENABLE_GMP == 1
#include "boost/multiprecision/gmp.hpp"
typedef boost::multiprecision::mpq_rational cpp_rational;
typedef boost::multiprecision::mpz_int cpp_int;
#else
typedef boost::multiprecision::cpp_rational cpp_rational;
typedef boost::multiprecision::cpp_int cpp_int;
#endif

enum ExtendedNumericType {
  bignum = 0,
  ratnum = 1,
  exact_complexnum = 2,
  inexact_complexnum = 3,
  fixnum = 4
};

class BignumInternal;
class RatnumInternal;
class ExactComplexnumInternal;
class InexactComplexnumInternal;

class ExtendedNumerics
{
  friend std::ostream &operator<<(std::ostream &os, const ExtendedNumerics &num);
  friend const ExtendedNumerics *operator+(int64_t left, const ExtendedNumerics &right);
  friend const ExtendedNumerics *operator-(int64_t left, const ExtendedNumerics &right);
  friend const ExtendedNumerics *operator*(int64_t left, const ExtendedNumerics &right);
  friend const ExtendedNumerics *operator/(int64_t left, const ExtendedNumerics &right);
  friend bool operator<(int64_t left, const ExtendedNumerics &right);
  friend bool operator==(int64_t left, const ExtendedNumerics &right);
  friend bool operator!=(int64_t left, const ExtendedNumerics &right);

 public:
  ExtendedNumericType type_;
  ExtendedNumerics(const ExtendedNumerics &to_copy) = delete;
  ExtendedNumerics(ExtendedNumerics &&to_move) = delete;
  virtual ~ExtendedNumerics() = default;
  virtual const std::string str() const = 0;
  virtual const ExtendedNumerics *operator+(const int64_t &right) const;
  virtual const ExtendedNumerics *operator-(const int64_t &right) const;
  virtual const ExtendedNumerics *operator*(const int64_t &right) const;
  virtual const ExtendedNumerics *operator/(const int64_t &right) const;
  virtual bool operator<(const int64_t &right) const;
  virtual bool operator==(const int64_t &right) const;
  virtual bool operator!=(const int64_t &right) const;
  virtual const ExtendedNumerics *operator+(const ExtendedNumerics &right) const;
  virtual const ExtendedNumerics *operator-(const ExtendedNumerics &right) const;
  virtual const ExtendedNumerics *operator*(const ExtendedNumerics &right) const;
  virtual const ExtendedNumerics *operator/(const ExtendedNumerics &right) const;
  virtual bool operator<(const ExtendedNumerics &right) const;
  virtual bool operator==(const ExtendedNumerics &right) const;
  virtual bool operator!=(const ExtendedNumerics &right) const;

 protected:
  explicit ExtendedNumerics(ExtendedNumericType type) : type_(type) {}
};

#endif //WASMEXTENDEDNUMERICS_SRC_EXTENDEDNUMERICS_HPP_
