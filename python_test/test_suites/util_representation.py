from fractions import Fraction
from functools import lru_cache
from typing import Union, Callable, Dict
from numeric import Numeric
from test_suites.config_and_defs import SUPPRESS_CONVERSION_FAILURES
from test_suites.util_random import random_fixnum, random_bignum, random_ratnum, random_exact_complexnum, \
    random_inexact_complexnum

from test_suites.util_types import ExactComplex, PyVal


@lru_cache(maxsize=2)
def get_transformation_dictionary() -> Dict[int, Callable[[Numeric], PyVal]]:
    transformations = {}
    fixnum_t = random_fixnum().type()
    bignum_t = random_bignum().type()
    ratnum_t = random_ratnum().type()
    exact_complexnum_t = random_exact_complexnum().type()
    inexact_complexnum_t = random_inexact_complexnum().type()
    transformations[fixnum_t] = fixnum_to_python_int
    transformations[bignum_t] = bignum_to_python_int
    transformations[ratnum_t] = ratnum_to_python_fraction
    transformations[exact_complexnum_t] = exact_complexnum_to_python_exactcomplex
    transformations[inexact_complexnum_t] = inexact_complexnum_to_python_complex
    return transformations


def exactnum_to_int_or_fraction(exactnum: Union[Numeric, str]) -> Union[int, Fraction]:
    if '/' in str(exactnum):
        n, d = str(exactnum).split('/')
        return Fraction(int(n), int(d))
    else:
        return int(str(exactnum))


def split_complexnum_str(complexnum_str: str):
    from re import search
    rev_complexnum_str = complexnum_str[::-1]
    index_of_div = search('[+-](?!e)', rev_complexnum_str).start()
    z, i = rev_complexnum_str[index_of_div + 1:][::-1], rev_complexnum_str[:index_of_div + 1][::-1].rstrip('i')
    if z == '' or i == '':
        raise RuntimeError("Could not split complexnum string: %s" % complexnum_str)
    return z, i


def exact_complexnum_to_python_exactcomplex(exact_complexnum: Numeric) -> ExactComplex:
    z, i = split_complexnum_str(str(exact_complexnum))
    i = i.rstrip('i')
    try:
        real = exactnum_to_int_or_fraction(z)
    except ValueError:
        if not SUPPRESS_CONVERSION_FAILURES:
            print("Could not convert \n%s\nto python val using %s" % (z, exactnum_to_int_or_fraction.__name__))
        raise RuntimeError

    try:
        imag = exactnum_to_int_or_fraction(i)
    except ValueError:
        if not SUPPRESS_CONVERSION_FAILURES:
            print("Could not convert \n%s\nto python val using %s" % (i, exactnum_to_int_or_fraction.__name__))
        raise RuntimeError

    return ExactComplex(real, imag)


def inexact_complexnum_to_python_complex(inexact_complexnum: Numeric) -> complex:
    z, i = split_complexnum_str(str(inexact_complexnum))
    i = i.rstrip('i')
    return complex(float(z), float(i))


def fixnum_to_python_int(fixnum: Numeric) -> int:
    converted = exactnum_to_int_or_fraction(fixnum)
    assert isinstance(converted, int)
    return converted


def bignum_to_python_int(bignum: Numeric) -> int:
    converted = exactnum_to_int_or_fraction(bignum)
    assert isinstance(converted, int)
    return converted


def ratnum_to_python_fraction(ratnum: Numeric) -> Fraction:
    converted = exactnum_to_int_or_fraction(ratnum)
    assert isinstance(converted, Fraction)
    return converted
