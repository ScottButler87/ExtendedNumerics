from numeric import Numeric
from unittest import TestCase
from typing import Any

RANDOM_TRIALS_PER_TEST = int(1e1)
SUPPRESS_CONVERSION_FAILURES = True
FLOAT_COMPARISON_REL_TOLERANCE = 0.0000000001

zero = Numeric("0")
one = Numeric("1")
negative_one = Numeric("-1")


def inexact_expectation(self: TestCase, left: Any, right: Any, msg='') -> None:
    self.assertAlmostEqual(left, right, delta=abs((FLOAT_COMPARISON_REL_TOLERANCE / 2) * (left + right)), msg=msg)


def monkeypatch_assert_complex_almost_equal(self: TestCase, left: complex, right: complex, msg: str) -> None:
    inexact_expectation(self, left.real, right.real, msg)
    inexact_expectation(self, left.imag, right.imag, msg)


TestCase.assertComplexAlmostEqual = monkeypatch_assert_complex_almost_equal
