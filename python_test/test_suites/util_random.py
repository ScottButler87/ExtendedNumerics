from numeric import Numeric
from random import randint, uniform, seed
from functools import partial
from typing import Tuple
from fractions import Fraction

from test_suites.util_types import ExactComplex

MIN_FIXNUM_VALUE = -4611686018427387904
MAX_FIXNUM_VALUE = 4611686018427387903

MAX_ARBITRARY_NUM_BITS = 256
seed(9439832)

random_float = partial(uniform, -1e12, 1e12)

zero = Numeric("0")
one = Numeric("1")
negative_one = Numeric("-1")


def generate_fixnum_a_less_than_b():
    a = random_python_int_inside_fixnum_range()
    b = random_python_int_inside_fixnum_range()
    while a == b:
        b = random_python_int_inside_fixnum_range()
    if a < b:
        return Numeric(str(a)), Numeric(str(b))
    else:
        return Numeric(str(b)), Numeric(str(a))


def non_zero_unequal_operands_from(random_generator):
    a = random_generator()
    if a == zero:
        a += one
    b = random_generator()
    while b == a:
        b = random_generator()
    if b == zero:
        b -= one
    return a, b


def random_fixnum_and_equiv_python_int() -> Tuple[Numeric, int]:
    py_int = random_python_int_inside_fixnum_range()
    return Numeric(str(py_int)), py_int


def random_inexact_complexnum_and_equiv_python_complex() -> Tuple[Numeric, complex]:
    real = random_float()
    imaginary = random_float()
    return Numeric(real, imaginary), complex(real, imaginary)


def random_ratnum_and_equiv_python_fraction():
    numerator = random_python_int_outside_fixnum_range()
    denominator = random_python_int_outside_fixnum_range()
    return Numeric(str(numerator), str(denominator)), Fraction(numerator, denominator)


def random_exact_complexnum_and_equiv_python_exactcomplex():
    real_numerator = random_python_int_outside_fixnum_range()
    real_denominator = random_python_int_outside_fixnum_range()
    imaginary_numerator = random_python_int_outside_fixnum_range()
    imaginary_denominator = random_python_int_outside_fixnum_range()
    return Numeric(str(real_numerator),
                   str(real_denominator),
                   str(imaginary_numerator),
                   str(imaginary_denominator)), ExactComplex(Fraction(real_numerator, real_denominator),
                                                             Fraction(imaginary_numerator, imaginary_denominator))


def random_python_int_outside_fixnum_range():
    candidate = randint(-(1 << MAX_ARBITRARY_NUM_BITS), 1 << MAX_ARBITRARY_NUM_BITS)
    while MIN_FIXNUM_VALUE < candidate < MAX_FIXNUM_VALUE:
        candidate = randint(-(1 << MAX_ARBITRARY_NUM_BITS), 1 << MAX_ARBITRARY_NUM_BITS)
    return candidate


def random_python_int_inside_fixnum_range():
    return randint(MIN_FIXNUM_VALUE, MAX_FIXNUM_VALUE)


def random_fixnum() -> Numeric:
    return Numeric(str(random_python_int_inside_fixnum_range()))


def random_inexact_complexnum() -> Numeric:
    return Numeric(random_float(), random_float())


def random_inexact_complexnum_and_equiv_python_floats() -> Tuple[Numeric, float, float]:
    real = random_float()
    imaginary = random_float()
    return Numeric(real, imaginary), real, imaginary


def random_bignum() -> Numeric:
    return Numeric(str(random_python_int_outside_fixnum_range()))


def random_bignum_and_equiv_python_int() -> Tuple[Numeric, int]:
    py_int = random_python_int_outside_fixnum_range()
    return Numeric(str(py_int)), py_int


def random_ratnum():
    return Numeric(str(random_python_int_outside_fixnum_range()), str(random_python_int_outside_fixnum_range()))


def random_exact_complexnum():
    return Numeric(str(random_python_int_outside_fixnum_range()), str(random_python_int_outside_fixnum_range()),
                   str(random_python_int_outside_fixnum_range()), str(random_python_int_outside_fixnum_range()))


ALL_RANDOM_NUMERIC_AND_PYVAL_GENERATORS = [
    random_fixnum_and_equiv_python_int,
    random_bignum_and_equiv_python_int,
    random_ratnum_and_equiv_python_fraction,
    random_exact_complexnum_and_equiv_python_exactcomplex,
    random_inexact_complexnum_and_equiv_python_complex
]

ALL_RANDOM_NUMERIC_GENERATORS_AND_NAMES = [
    (random_fixnum_and_equiv_python_int, 'fixnum'),
    (random_inexact_complexnum_and_equiv_python_complex, 'inexact_complexnum'),
    (random_bignum_and_equiv_python_int, 'bignum'),
    (random_ratnum_and_equiv_python_fraction, 'ratnum'),
    (random_exact_complexnum_and_equiv_python_exactcomplex, 'exact_complexnum')
]
