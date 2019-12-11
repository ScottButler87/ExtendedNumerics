//
// Created by scott on 12/9/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_RATNUMINTERNAL_HPP_
#define WASMEXTENDEDNUMERICS_SRC_RATNUMINTERNAL_HPP_

#include "ExtendedNumerics.hpp"

class RatnumInternal : public ExtendedNumerics
{
  friend std::ostream &operator<<(std::ostream &, const RatnumInternal &);
  friend const RatnumInternal *operator+(int64_t, const RatnumInternal &);
  friend const RatnumInternal *operator-(int64_t, const RatnumInternal &);
  friend const RatnumInternal *operator*(int64_t, const RatnumInternal &);
  friend const RatnumInternal *operator/(int64_t, const RatnumInternal &);
  friend bool operator<(int64_t, const RatnumInternal &);
  friend bool operator==(int64_t, const RatnumInternal &);
  friend bool operator!=(int64_t, const RatnumInternal &);
  friend class BignumInternal;
  friend class ExactComplexnumInternal;
  friend class InexactComplexnumInternal;
  friend union NumericInternal;

 public:
  RatnumInternal(const char *numerator, const char *denominator);
  RatnumInternal(const std::string &numerator, const std::string &denominator)
      : RatnumInternal(numerator.c_str(), denominator.c_str()) {}
  explicit RatnumInternal(cpp_rational &&int_rep)
      : ExtendedNumerics(ratnum), internal_representation_(std::move(int_rep)) {}
  RatnumInternal(const RatnumInternal &to_copy) : RatnumInternal(cpp_rational(to_copy.internal_representation_)) {}
  RatnumInternal(RatnumInternal &&to_move) : RatnumInternal(std::move(to_move.internal_representation_)) {}


  FORCE_INLINE const std::string str() const override {\
    return internal_representation_.str();\
    };

  const ExtendedNumerics *operator+(const ExtendedNumerics &right) const override;
  const RatnumInternal *operator+(const int64_t &right) const override;
  virtual const RatnumInternal *operator+(const BignumInternal &right) const;
  virtual const RatnumInternal *operator+(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator+(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator+(const InexactComplexnumInternal &right) const;
  const ExtendedNumerics *operator-(const ExtendedNumerics &right) const override;
  const RatnumInternal *operator-(const int64_t &right) const override;
  virtual const RatnumInternal *operator-(const BignumInternal &right) const;
  virtual const RatnumInternal *operator-(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator-(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator-(const InexactComplexnumInternal &right) const;
  const ExtendedNumerics *operator*(const ExtendedNumerics &right) const override;
  const RatnumInternal *operator*(const int64_t &right) const override;
  virtual const RatnumInternal *operator*(const BignumInternal &right) const;
  virtual const RatnumInternal *operator*(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator*(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator*(const InexactComplexnumInternal &right) const;
  const ExtendedNumerics *operator/(const ExtendedNumerics &right) const override;
  const RatnumInternal *operator/(const int64_t &right) const override;
  virtual const RatnumInternal *operator/(const BignumInternal &right) const;
  virtual const RatnumInternal *operator/(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator/(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator/(const InexactComplexnumInternal &right) const;

  bool operator==(const int64_t &right) const override;
  bool operator==(const ExtendedNumerics &right) const override;
  virtual bool operator==(const BignumInternal &right) const;
  virtual bool operator==(const RatnumInternal &right) const;
  virtual bool operator==(const ExactComplexnumInternal &right) const;
  virtual bool operator==(const InexactComplexnumInternal &right) const;
  bool operator!=(const int64_t &right) const override;
  bool operator!=(const ExtendedNumerics &right) const override;
  virtual bool operator!=(const BignumInternal &right) const;
  virtual bool operator!=(const RatnumInternal &right) const;
  virtual bool operator!=(const ExactComplexnumInternal &right) const;
  virtual bool operator!=(const InexactComplexnumInternal &right) const;
  bool operator<(const int64_t &right) const override;
  bool operator<(const ExtendedNumerics &right) const override;
  virtual bool operator<(const BignumInternal &right) const;
  virtual bool operator<(const RatnumInternal &right) const;

 private:
  cpp_rational internal_representation_;
};

#endif //WASMEXTENDEDNUMERICS_SRC_RATNUMINTERNAL_HPP_
