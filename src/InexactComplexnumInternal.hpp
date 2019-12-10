//
// Created by scott on 12/9/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_INEXACTCOMPLEXNUMINTERNAL_HPP_
#define WASMEXTENDEDNUMERICS_SRC_INEXACTCOMPLEXNUMINTERNAL_HPP_

#include "ExtendedNumerics.hpp"

class InexactComplexnumInternal : public ExtendedNumerics
{
  friend std::ostream &operator<<(std::ostream &os, const InexactComplexnumInternal &num);
  friend const InexactComplexnumInternal *operator+(int64_t, const InexactComplexnumInternal &);
  friend const InexactComplexnumInternal *operator-(int64_t, const InexactComplexnumInternal &);
  friend const InexactComplexnumInternal *operator*(int64_t, const InexactComplexnumInternal &);
  friend const InexactComplexnumInternal *operator/(int64_t, const InexactComplexnumInternal &);
  friend class BignumInternal;
  friend class RatnumInternal;
  friend class ExactComplexnumInternal;
  friend union NumericInternal;

 public:
  InexactComplexnumInternal(double real, double imaginary)
      : ExtendedNumerics(inexact_complexnum), real_(real), imaginary_(imaginary) {}
  InexactComplexnumInternal(const InexactComplexnumInternal &to_copy)
      : InexactComplexnumInternal(to_copy.real_, to_copy.imaginary_) {}
  InexactComplexnumInternal(InexactComplexnumInternal &&to_move) noexcept
      : InexactComplexnumInternal(to_move.real_, to_move.imaginary_) {}

  FORCE_INLINE std::string str() const override
  {
    std::stringstream out;
    if (imaginary_ < 0)
    {
      out << std::setprecision(64) << real_ << " " << imaginary_ << "i";
    }
    else
    {
      out << std::setprecision(64) << real_ << " +" << imaginary_ << "i";
    }
    return out.str();
  }

  virtual const ExtendedNumerics *operator+(const ExtendedNumerics &right) const;
  virtual const InexactComplexnumInternal *operator+(const int64_t &right) const;
  virtual const InexactComplexnumInternal *operator+(const BignumInternal &right) const;
  virtual const InexactComplexnumInternal *operator+(const RatnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator+(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator+(const InexactComplexnumInternal &right) const;
  virtual const ExtendedNumerics *operator-(const ExtendedNumerics &right) const;
  virtual const InexactComplexnumInternal *operator-(const int64_t &right) const;
  virtual const InexactComplexnumInternal *operator-(const BignumInternal &right) const;
  virtual const InexactComplexnumInternal *operator-(const RatnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator-(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator-(const InexactComplexnumInternal &right) const;
  virtual const ExtendedNumerics *operator*(const ExtendedNumerics &right) const;
  virtual const InexactComplexnumInternal *operator*(const int64_t &right) const;
  virtual const InexactComplexnumInternal *operator*(const BignumInternal &right) const;
  virtual const InexactComplexnumInternal *operator*(const RatnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator*(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator*(const InexactComplexnumInternal &right) const;
  virtual const ExtendedNumerics *operator/(const ExtendedNumerics &right) const;
  virtual const InexactComplexnumInternal *operator/(const int64_t &right) const;
  virtual const InexactComplexnumInternal *operator/(const BignumInternal &right) const;
  virtual const InexactComplexnumInternal *operator/(const RatnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator/(const ExactComplexnumInternal &right) const;
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

 private:
  double real_;
  double imaginary_;
};

#endif //WASMEXTENDEDNUMERICS_SRC_INEXACTCOMPLEXNUMINTERNAL_HPP_
