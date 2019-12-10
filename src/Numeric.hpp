//
// Created by scott on 12/9/19.
//

#ifndef WASMEXTENDEDNUMERICS_SRC_NUMERIC_HPP_
#define WASMEXTENDEDNUMERICS_SRC_NUMERIC_HPP_

#include "ExtendedNumerics.hpp"
#include "BignumInternal.hpp"
#include "RatnumInternal.hpp"
#include "ExactComplexnumInternal.hpp"
#include "InexactComplexnumInternal.hpp"
#include "util.hpp"

#ifndef FORCE_INLINE
#ifndef SWIGGING_EXTENSION
  #define FORCE_INLINE __attribute__((always_inline)) inline
#else
  #define FORCE_INLINE
#endif
#endif

class Numeric;

union NumericInternal {
  friend Numeric;
  int64_t fixnum_;
  const ExtendedNumerics *extended_numeric_;
  FORCE_INLINE bool isFixnum() const { return u64(fixnum_) & u64(1); }
  FORCE_INLINE int64_t asFixnum() const {
    if (fixnum_ < 0) {
      return i64((u64(fixnum_) >> u64(1)) | (u64(1) << u64(63)));
    } else {
      return i64(u64(fixnum_) >> u64(1));
    }
  }
  FORCE_INLINE std::string str() {
    if (this->isFixnum()) {
      return std::to_string(this->asFixnum());
    }
    return extended_numeric_->str();
  }
  ~NumericInternal() { if (!isFixnum()) { delete extended_numeric_; }}

  explicit NumericInternal(int64_t num) noexcept
      : fixnum_((u64(num) << u64(1)) | u64(1)) {}
  explicit NumericInternal(const ExtendedNumerics *num) : extended_numeric_(num) {}
  explicit NumericInternal(const std::string &digits) {
    if (numeric_string_fits_in_signed_fixnum(digits)) {
      fixnum_ = (u64(std::stoll(digits)) << u64(1)) | u64(1);
    } else {
      extended_numeric_ = new BignumInternal(digits);
    }
  }
  explicit NumericInternal(const char *digits) {
    if (numeric_string_fits_in_signed_fixnum(digits)) {
      fixnum_ = (u64(std::stoll(digits)) << u64(1) | u64(1));
    } else {
      extended_numeric_ = new BignumInternal(digits);
    }
  }
  NumericInternal(double real, double imaginary)
      : extended_numeric_(new InexactComplexnumInternal(real, imaginary)) {}
  NumericInternal(const std::string &numerator, const std::string &denominator)
      : extended_numeric_(new RatnumInternal(numerator, denominator)) {}
  NumericInternal(const char *numerator, const char *denominator)
      : extended_numeric_(new RatnumInternal(numerator, denominator)) {}
  NumericInternal(const std::string &real_numerator,
                  const std::string &real_denominator,
                  const std::string &imaginary_numerator,
                  const std::string &imaginary_denominator)
      : extended_numeric_(new ExactComplexnumInternal(real_numerator,
                                                      real_denominator,
                                                      imaginary_numerator,
                                                      imaginary_denominator)) {};
  NumericInternal(const char *real_numerator,
                  const char *real_denominator,
                  const char *imaginary_numerator,
                  const char *imaginary_denominator)
      : extended_numeric_(new ExactComplexnumInternal(real_numerator,
                                                      real_denominator,
                                                      imaginary_numerator,
                                                      imaginary_denominator)) {};
  NumericInternal(cpp_rational &&real, cpp_rational &&imaginary) : extended_numeric_(
      new ExactComplexnumInternal(std::move(real), std::move(imaginary))
  ) {}
  NumericInternal(cpp_int &&internal) : extended_numeric_(
      new BignumInternal(std::move(internal))) {}
  NumericInternal(cpp_rational &&internal) : extended_numeric_(
      new RatnumInternal(std::move(internal))) {}
  NumericInternal(const NumericInternal &to_copy) {
    if (to_copy.isFixnum()) {
      this->fixnum_ = to_copy.fixnum_;
    } else {
      switch (to_copy.extended_numeric_->type_) {
        case bignum:
          this->extended_numeric_ =
              new BignumInternal(*dynamic_cast<const BignumInternal *>(to_copy.extended_numeric_));
          break;
        case ratnum:
          this->extended_numeric_ =
              new RatnumInternal(*dynamic_cast<const RatnumInternal *>(to_copy.extended_numeric_));
          break;
        case exact_complexnum:
          this->extended_numeric_ =
              new ExactComplexnumInternal(*dynamic_cast<const ExactComplexnumInternal *>(to_copy.extended_numeric_));
          break;
        case inexact_complexnum:
          this->extended_numeric_ =
              new InexactComplexnumInternal(*dynamic_cast<const InexactComplexnumInternal *>(to_copy.extended_numeric_));
          break;
        case fixnum:
          throw std::logic_error("In NumericInternal copy constructor, isFixnum returned false but extended_numeric_.type_ was fixnum");
      }
    }
  }
  NumericInternal(NumericInternal &&to_move) {
    if (to_move.isFixnum()) {
      this->fixnum_ = to_move.fixnum_;
    } else {
      this->extended_numeric_ = to_move.extended_numeric_;
      to_move.fixnum_ |= 1u;
    }

  }
};

class Numeric {
 public:
  friend std::ostream &operator<<(std::ostream &os, const Numeric &num);
  friend std::ostream &operator<<(std::ostream &os, const Numeric &&num);

  explicit Numeric(int64_t num) noexcept : internal_representation_(num) {}
  explicit Numeric(const ExtendedNumerics *num) : internal_representation_(num) {}
  explicit Numeric(const std::string &digits) : internal_representation_(digits) {}
  explicit Numeric(const char *digits) : internal_representation_(digits) {}
  Numeric(double real, double imaginary) : internal_representation_(real, imaginary) {}
  Numeric(cpp_int &&internal) : internal_representation_(std::move(internal)) {}
  Numeric(cpp_rational &&internal) : internal_representation_(std::move(internal)) {}
  Numeric(cpp_rational &&real, cpp_rational &&imaginary) : internal_representation_(
      std::move(real), std::move(imaginary)) {}
  Numeric(const std::string &numerator, const std::string &denominator)
      : internal_representation_(numerator, denominator) {}
  Numeric(const char *numerator, const char *denominator)
      : internal_representation_(numerator, denominator) {}
  Numeric(const std::string &real_numerator, const std::string &real_denominator,
          const std::string &imaginary_numerator, const std::string &imaginary_denominator)
      : internal_representation_(real_numerator,
                                 real_denominator,
                                 imaginary_numerator,
                                 imaginary_denominator) {}
  Numeric(const char *real_numerator, const char *real_denominator,
          const char *imaginary_numerator, const char *imaginary_denominator)
      : internal_representation_(real_numerator,
                                 real_denominator,
                                 imaginary_numerator,
                                 imaginary_denominator) {}
  explicit Numeric(Numeric &&to_move) noexcept
      : internal_representation_(std::move(to_move.internal_representation_))  {}
  Numeric(const Numeric &to_copy) : internal_representation_(to_copy.internal_representation_) {}

  FORCE_INLINE std::string str() {
    return internal_representation_.str();
  }

  ExtendedNumericType type() const {
    if (internal_representation_.isFixnum()) { return fixnum; }
    else {
      return internal_representation_.extended_numeric_->type_;
    }
  }

  FORCE_INLINE Numeric operator+(const Numeric &right)
  {
    bool this_is_fixnum = this->internal_representation_.isFixnum();
    bool right_is_fixnum = right.internal_representation_.isFixnum();
    if (this_is_fixnum)
    {
      int64_t this_as_fixnum = this->internal_representation_.asFixnum();
      if (right_is_fixnum)
      {
        int64_t right_as_fixnum = right.internal_representation_.asFixnum();
        int64_t result;
        if (added_without_fixnum_overflow(this_as_fixnum, right_as_fixnum, result))
        {
          return Numeric(result);
        }
        else
        {
          return Numeric(static_cast<cpp_int>(cpp_int(this_as_fixnum) + right_as_fixnum));
        }
      }
      else
      {
        return Numeric(this_as_fixnum + *right.internal_representation_.extended_numeric_);
      }
    }
    else
    {
      if (right_is_fixnum)
      {
        return Numeric(*this->internal_representation_.extended_numeric_ + right.internal_representation_.asFixnum());
      }
      else
      {
        return Numeric(*this->internal_representation_.extended_numeric_ + *right.internal_representation_.extended_numeric_);
      }
    }
  }

  FORCE_INLINE Numeric operator-(const Numeric &right)
  {
    bool this_is_fixnum = this->internal_representation_.isFixnum();
    bool right_is_fixnum = right.internal_representation_.isFixnum();
    if (this_is_fixnum)
    {
      int64_t this_as_fixnum = this->internal_representation_.asFixnum();
      if (right_is_fixnum)
      {
        int64_t right_as_fixnum = right.internal_representation_.asFixnum();
        int64_t result;
        if (subtracted_without_fixnum_overflow(this_as_fixnum, right_as_fixnum, result))
        {
          return Numeric(result);
        }
        else
        {
          return Numeric(static_cast<cpp_int>(cpp_int(this_as_fixnum) - right_as_fixnum));
        }
      }
      else
      {
        return Numeric(this_as_fixnum - *right.internal_representation_.extended_numeric_);
      }
    }
    else
    {
      if (right_is_fixnum)
      {
        return Numeric(*this->internal_representation_.extended_numeric_ - right.internal_representation_.asFixnum());
      }
      else
      {
        return Numeric(*this->internal_representation_.extended_numeric_ - *right.internal_representation_.extended_numeric_);
      }
    }
  }

  FORCE_INLINE Numeric operator*(const Numeric &right)
  {
    bool this_is_fixnum = this->internal_representation_.isFixnum();
    bool right_is_fixnum = right.internal_representation_.isFixnum();
    if (this_is_fixnum)
    {
      int64_t this_as_fixnum = this->internal_representation_.asFixnum();
      if (right_is_fixnum)
      {
        int64_t right_as_fixnum = right.internal_representation_.asFixnum();
        int64_t result;
        if (multiplied_without_fixnum_overflow(this_as_fixnum, right_as_fixnum, result))
        {
          return Numeric(result);
        }
        else
        {
          return Numeric(static_cast<cpp_int>(cpp_int(this_as_fixnum) * right_as_fixnum));
        }
      }
      else
      {
        return Numeric(this_as_fixnum * *right.internal_representation_.extended_numeric_);
      }
    }
    else
    {
      if (right_is_fixnum)
      {
        return Numeric(*this->internal_representation_.extended_numeric_ * right.internal_representation_.asFixnum());
      }
      else
      {
        return Numeric(*this->internal_representation_.extended_numeric_ * *right.internal_representation_.extended_numeric_);
      }
    }
  }

  FORCE_INLINE Numeric operator/(const Numeric &right)
  {
    bool this_is_fixnum = this->internal_representation_.isFixnum();
    bool right_is_fixnum = right.internal_representation_.isFixnum();
    if (this_is_fixnum)
    {
      int64_t this_as_fixnum = this->internal_representation_.asFixnum();
      if (right_is_fixnum)
      {
        int64_t right_as_fixnum = right.internal_representation_.asFixnum();
        int64_t result;
        if (divided_without_fixnum_overflow_or_precision_loss(this_as_fixnum, right_as_fixnum, result))
        {
          return Numeric(result);
        }
        else
        {
          return Numeric(static_cast<cpp_rational>(cpp_rational(this_as_fixnum) / right_as_fixnum));
        }
      }
      else
      {
        return Numeric(this_as_fixnum / *right.internal_representation_.extended_numeric_);
      }
    }
    else
    {
      if (right_is_fixnum)
      {
        return Numeric(*this->internal_representation_.extended_numeric_ / right.internal_representation_.asFixnum());
      }
      else
      {
        return Numeric(*this->internal_representation_.extended_numeric_ / *right.internal_representation_.extended_numeric_);
      }
    }
  }

  friend Numeric operator+(int64_t left, const Numeric &right) {
    return Numeric(left) + right;
  }
  friend Numeric operator-(int64_t left, const Numeric &right) {
    return Numeric(left) - right;
  }
  friend Numeric operator*(int64_t left, const Numeric &right) {
    return Numeric(left) * right;
  }
  friend Numeric operator/(int64_t left, const Numeric &right) {
    return Numeric(left) / right;
  }
  bool operator==(const Numeric &right) const;
  bool operator<(const Numeric &right) const;
  explicit operator int64_t() const {
    if (internal_representation_.isFixnum()) {
      return internal_representation_.asFixnum();
    } else {
      // TODO add explicit conversions for extended numerics
      return 0;
    }
  }
 private:
  NumericInternal internal_representation_;
};


#endif //WASMEXTENDEDNUMERICS_SRC_NUMERIC_HPP_
