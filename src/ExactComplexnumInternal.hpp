//
// Created by scott on 12/9/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_EXACTCOMPLEXNUMINTERNAL_CPP_HPP_
#define WASMEXTENDEDNUMERICS_SRC_EXACTCOMPLEXNUMINTERNAL_CPP_HPP_

#include "ExtendedNumerics.hpp"

class ExactComplexnumInternal : public ExtendedNumerics
{
  friend std::ostream &operator<<(std::ostream &os, const ExactComplexnumInternal &num);
  friend const ExactComplexnumInternal *operator+(int64_t, const ExactComplexnumInternal &);
  friend const ExactComplexnumInternal *operator-(int64_t, const ExactComplexnumInternal &);
  friend const ExactComplexnumInternal *operator*(int64_t, const ExactComplexnumInternal &);
  friend const ExactComplexnumInternal *operator/(int64_t, const ExactComplexnumInternal &);
  friend bool operator==(int64_t, const ExactComplexnumInternal &);
  friend bool operator!=(int64_t, const ExactComplexnumInternal &);
  friend class BignumInternal;
  friend class RatnumInternal;
  friend class InexactComplexnumInternal;
  friend union NumericInternal;

 public:
  ExactComplexnumInternal(const char *real_numerator,
                          const char *real_denominator,
                          const char *imaginary_numerator,
                          const char *imaginary_denominator);
  ExactComplexnumInternal(const std::string &real_numerator,
                          const std::string &real_denominator,
                          const std::string &imaginary_numerator,
                          const std::string &imaginary_denominator)
      : ExactComplexnumInternal(real_numerator.c_str(), real_denominator.c_str(),
                                imaginary_numerator.c_str(), imaginary_denominator.c_str()) {}
  ExactComplexnumInternal(cpp_rational &&real, cpp_rational &&imaginary)
      : ExtendedNumerics(exact_complexnum),
        real_(std::move(real)),
        imaginary_(std::move(imaginary)) {}
  ExactComplexnumInternal(const ExactComplexnumInternal &to_copy)
      : ExactComplexnumInternal(cpp_rational(to_copy.real_), cpp_rational(to_copy.imaginary_)) {}
  ExactComplexnumInternal(ExactComplexnumInternal &&to_move)
      : ExactComplexnumInternal(std::move(to_move.real_), std::move(to_move.imaginary_)) {}

  FORCE_INLINE const std::string str() const override
  {
    std::stringstream ss;
    ss << real_;
    if (imaginary_ >= 0)
      ss << "+";
    ss << imaginary_;
    return ss.str();
  }
  const ExtendedNumerics *operator+(const ExtendedNumerics &right) const override;
  const ExactComplexnumInternal *operator+(const int64_t &right) const override;
  virtual const ExactComplexnumInternal *operator+(const BignumInternal &right) const;
  virtual const ExactComplexnumInternal *operator+(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator+(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator+(const InexactComplexnumInternal &right) const;
  const ExtendedNumerics *operator-(const ExtendedNumerics &right) const override;
  const ExactComplexnumInternal *operator-(const int64_t &right) const override;
  virtual const ExactComplexnumInternal *operator-(const BignumInternal &right) const;
  virtual const ExactComplexnumInternal *operator-(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator-(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator-(const InexactComplexnumInternal &right) const;
  const ExtendedNumerics *operator*(const ExtendedNumerics &right) const override;
  const ExactComplexnumInternal *operator*(const int64_t &right) const override;
  virtual const ExactComplexnumInternal *operator*(const BignumInternal &right) const;
  virtual const ExactComplexnumInternal *operator*(const RatnumInternal &right) const;
  virtual const ExactComplexnumInternal *operator*(const ExactComplexnumInternal &right) const;
  virtual const InexactComplexnumInternal *operator*(const InexactComplexnumInternal &right) const;
  const ExtendedNumerics *operator/(const ExtendedNumerics &right) const override;
  const ExactComplexnumInternal *operator/(const int64_t &right) const override;
  virtual const ExactComplexnumInternal *operator/(const BignumInternal &right) const;
  virtual const ExactComplexnumInternal *operator/(const RatnumInternal &right) const;
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

 private:
  cpp_rational real_;
  cpp_rational imaginary_;
};

#endif //WASMEXTENDEDNUMERICS_SRC_EXACTCOMPLEXNUMINTERNAL_CPP_HPP_
