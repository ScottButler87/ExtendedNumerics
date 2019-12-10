//
// Created by scott on 12/9/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_BIGNUMINTERNAL_HPP_
#define WASMEXTENDEDNUMERICS_SRC_BIGNUMINTERNAL_HPP_

#include "ExtendedNumerics.hpp"
#include "RatnumInternal.hpp"

class BignumInternal : public ExtendedNumerics {
  friend std::ostream &operator<<(std::ostream &os, const BignumInternal &num);
  friend const BignumInternal *operator+(int64_t, const BignumInternal &);
  friend const BignumInternal *operator-(int64_t, const BignumInternal &);
  friend const BignumInternal *operator*(int64_t, const BignumInternal &);
  friend const ExtendedNumerics *operator/(int64_t, const BignumInternal &);
  friend bool operator<(int64_t, const BignumInternal &);
  friend bool operator==(int64_t, const BignumInternal &);
  friend bool operator!=(int64_t, const BignumInternal &);
  friend class RatnumInternal;
  friend class ExactComplexnumInternal;
  friend class InexactComplexnumInternal;
  friend union NumericInternal;
 public:
  explicit BignumInternal(const char *digits) : ExtendedNumerics(bignum), internal_representation_(digits) {}
  explicit BignumInternal(const std::string &digits)
      : BignumInternal(digits.c_str()) {}
  explicit BignumInternal(const cpp_int &int_rep)
      : ExtendedNumerics(bignum), internal_representation_(int_rep) {}
  explicit BignumInternal(cpp_int &&int_rep) noexcept
      : ExtendedNumerics(bignum), internal_representation_(std::move(int_rep)) {}
  BignumInternal(const BignumInternal &to_copy) : BignumInternal(cpp_int(to_copy.internal_representation_)) {}
  BignumInternal(BignumInternal &&to_move) : BignumInternal(std::move(to_move.internal_representation_)) {}

  FORCE_INLINE const std::string str() const override {
    return internal_representation_.str();
  };

  virtual const ExtendedNumerics *operator+(const ExtendedNumerics &right) const;
  virtual const BignumInternal *operator+(const int64_t &right) const;
  virtual const BignumInternal *operator+(const BignumInternal &right) const;
  virtual const RatnumInternal *operator+(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator+(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator+(const InexactComplexnumInternal &right) const;
  virtual const ExtendedNumerics *operator-(const ExtendedNumerics &right) const;
  virtual const BignumInternal *operator-(const int64_t &right) const;
  virtual const BignumInternal *operator-(const BignumInternal &right) const;
  virtual const RatnumInternal *operator-(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator-(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator-(const InexactComplexnumInternal &right) const;
  virtual const ExtendedNumerics *operator*(const ExtendedNumerics &right) const;
  virtual const BignumInternal *operator*(const int64_t &right) const;
  virtual const BignumInternal *operator*(const BignumInternal &right) const;
  virtual const RatnumInternal *operator*(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator*(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator*(const InexactComplexnumInternal &right) const;
  virtual const ExtendedNumerics *operator/(const ExtendedNumerics &right) const;
  virtual const RatnumInternal *operator/(const int64_t &right) const;
  virtual const RatnumInternal *operator/(const BignumInternal &right) const;
  virtual const RatnumInternal *operator/(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator/(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator/(const InexactComplexnumInternal &right) const;

  virtual bool operator==(const int64_t &right) const;
  virtual bool operator==(const ExtendedNumerics &right) const;
  virtual bool operator==(const BignumInternal &right) const;
  virtual bool operator==(const RatnumInternal &right) const;
  virtual bool operator==(const ExactComplexnumInternal &right) const;
  virtual bool operator==(const InexactComplexnumInternal &right) const;
  virtual bool operator!=(const int64_t &right) const;
  virtual bool operator!=(const ExtendedNumerics &right) const;
  virtual bool operator!=(const BignumInternal &right) const;
  virtual bool operator!=(const RatnumInternal &right) const;
  virtual bool operator!=(const ExactComplexnumInternal &right) const;
  virtual bool operator!=(const InexactComplexnumInternal &right) const;
  virtual bool operator<(const int64_t &right) const;
  virtual bool operator<(const ExtendedNumerics &right) const;
  virtual bool operator<(const BignumInternal &right) const;
  virtual bool operator<(const RatnumInternal &right) const;

 private:
  cpp_int internal_representation_;
};

#endif //WASMEXTENDEDNUMERICS_SRC_BIGNUMINTERNAL_HPP_
