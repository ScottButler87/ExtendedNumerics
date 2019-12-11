from fractions import Fraction
from typing import TypeVar, Union, Callable, Tuple
from math import isclose

from numeric import Numeric

FLOAT_COMPARISON_REL_TOLERANCE = 0.00000000001


def calc_complex_div(left_real, left_imag, right_real, right_imaginary):
    from math import pow
    divisor = pow(right_real, 2) + pow(right_imaginary, 2)
    real = (left_real * right_real) + (left_imag * right_imaginary)
    imag = (right_real * left_imag) - (left_real * right_imaginary)
    return complex(real/divisor, imag/divisor)


def calc_complex_mul(left_real, left_imag, right_real, right_imag):
    real = (left_real * right_real) - (left_imag * right_imag)
    imag = (left_real * right_imag) + (left_imag * right_real)
    return complex(real, imag)


class ExactComplex:
    def __init__(self, real: [int, Fraction], imag: [int, Fraction]):
        self.real: Union[int, Fraction] = real
        self.imag: Union[int, Fraction] = imag

    def __str__(self):
        return '%s %si' % (self.real, self.imag)

    def __eq__(self, other):
        if isinstance(other, complex):
            return isclose(float(self.real), other.real, rel_tol=FLOAT_COMPARISON_REL_TOLERANCE)\
               and isclose(float(self.imag), other.imag, rel_tol=FLOAT_COMPARISON_REL_TOLERANCE)
        elif isinstance(other, ExactComplex):
            return self.real == other.real and self.imag == other.imag
        elif isinstance(other, Fraction):
            return self.imag == 0 and self.real == other
        elif isinstance(other, int):
            return self.imag == 0 and self.real == other
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__eq__" % type(other))

    def __add__(self, other):
        if isinstance(other, complex):
            return complex(float(self.real) + other.real, float(self.imag) + other.imag)
        elif isinstance(other, int):
            return ExactComplex(self.real + other, self.imag)
        elif isinstance(other, Fraction):
            return ExactComplex(self.real + other, self.imag)
        elif isinstance(other, ExactComplex):
            return ExactComplex(self.real + other.real, self.imag + other.imag)
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__add__" % type(other))

    def __radd__(self, other):
        if isinstance(other, complex):
            return complex(other.real + float(self.real), other.imag + float(self.imag))
        elif isinstance(other, int):
            return ExactComplex(other + self.real, self.imag)
        elif isinstance(other, Fraction):
            return ExactComplex(other + self.real, self.imag)
        elif isinstance(other, ExactComplex):
            return ExactComplex(other.real + self.real, other.imag + self.imag)
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__radd__" % type(other))

    def __sub__(self, other):
        if isinstance(other, complex):
            return complex(float(self.real) - other.real, float(self.imag) - other.imag)
        elif isinstance(other, int):
            return ExactComplex(self.real - other, self.imag)
        elif isinstance(other, Fraction):
            return ExactComplex(self.real - other, self.imag)
        elif isinstance(other, ExactComplex):
            return ExactComplex(self.real - other.real, self.imag - other.imag)
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__sub__" % type(other))

    def __rsub__(self, other):
        if isinstance(other, complex):
            return complex(other.real - float(self.real), other.imag - float(self.imag))
        elif isinstance(other, int):
            return ExactComplex(other - self.real, -self.imag)
        elif isinstance(other, Fraction):
            return ExactComplex(other - self.real, -self.imag)
        elif isinstance(other, ExactComplex):
            return ExactComplex(other.real - self.real, other.imag - self.imag)
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__rsub__" % type(other))

    def __mul__(self, other):
        if isinstance(other, complex):
            return calc_complex_mul(self.real, self.imag, other.real, other.imag)
        elif isinstance(other, int):
            return calc_complex_mul(self.real, self.imag, other, 0)
        elif isinstance(other, Fraction):
            return calc_complex_mul(self.real, self.imag, other, 0)
        elif isinstance(other, ExactComplex):
            return calc_complex_mul(self.real, self.imag, other.real, other.imag)
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__mul__" % type(other))

    def __rmul__(self, other):
        if isinstance(other, complex):
            return calc_complex_mul(other.real, other.imag, self.real, self.imag)
        elif isinstance(other, int):
            return calc_complex_mul(other, 0, self.real, self.imag)
        elif isinstance(other, Fraction):
            return calc_complex_mul(other, 0, self.real, self.imag)
        elif isinstance(other, ExactComplex):
            return calc_complex_mul(other.real, other.imag, self.real, self.imag)
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__rmul__" % type(other))

    def __truediv__(self, other):
        if isinstance(other, complex):
            return calc_complex_div(self.real, self.imag, other.real, other.imag)
        elif isinstance(other, int):
            return calc_complex_div(self.real, self.imag, other, 0)
        elif isinstance(other, Fraction):
            return calc_complex_div(self.real, self.imag, other, 0)
        elif isinstance(other, ExactComplex):
            return calc_complex_div(self.real, self.imag, other.real, other.imag)
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__truediv__" % type(other))

    def __rtruediv__(self, other):
        if isinstance(other, complex):
            return calc_complex_div(other.real, other.imag, self.real, self.imag)
        elif isinstance(other, int):
            return calc_complex_div(other, 0, self.real, self.imag)
        elif isinstance(other, Fraction):
            return calc_complex_div(other, 0, self.real, self.imag)
        elif isinstance(other, ExactComplex):
            return calc_complex_div(other.real, other.imag, self.real, self.imag)
        else:
            raise Exception("Unexpected type %s encountered in ExactComplex__rtruediv__" % type(other))


# rational wrapper over fractions
class Ratnum(Fraction):
    def __init__(self, *args, **kwargs):
        super().__init__(self, args, kwargs)

    def __eq__(self, other):
        if isinstance(other, complex):
            return other.imag == 0 and isclose(float(self), other.real, rel_tol=FLOAT_COMPARISON_REL_TOLERANCE)
        elif isinstance(other, float):
            return isclose(float(self), other, rel_tol=FLOAT_COMPARISON_REL_TOLERANCE)
        else:
            return super().__eq__(other)



    # def __add__(self, other):
    #     if isinstance(other, complex):
    #         return complex(float(self.real) + other.real, float(self.imag) + other.imag)
    # def __sub__(self, other):
    #     if isinstance(other, complex):
    #         return complex(float(self.real) - other.real, float(self.imag) - other.imag)
    # def __mul__(self, other):
    #     if isinstance(other, complex):
    #         return calc_complex_mul(self.real, self.imag, other.real, other.imag)
    # def __truediv__(self, other):
    #     if isinstance(other, complex):
    #         return calc_complex_div(self.real, self.imag, other.real, other.imag)

PyVal = TypeVar('PyVal', int, Fraction, complex, ExactComplex)
Operand = Union[PyVal, Numeric]
RandomGenerator = Callable[[], Tuple[Numeric, PyVal]]
