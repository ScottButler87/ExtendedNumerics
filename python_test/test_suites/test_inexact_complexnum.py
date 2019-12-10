from unittest import TestCase

from test_suites.config_and_defs import RANDOM_TRIALS_PER_TEST

from test_suites.util_random import\
    random_inexact_complexnum_and_equiv_python_complex,\
    random_fixnum_and_equiv_python_int,\
    random_bignum_and_equiv_python_int,\
    random_ratnum_and_equiv_python_fraction,\
    random_exact_complexnum_and_equiv_python_exactcomplex

from test_suites.util_operations import BoundOperation, COMPLEX_OPERATIONS

numeric_random_generators = [
    random_fixnum_and_equiv_python_int,
    random_bignum_and_equiv_python_int,
    random_ratnum_and_equiv_python_fraction,
    random_exact_complexnum_and_equiv_python_exactcomplex,
    random_inexact_complexnum_and_equiv_python_complex
]


class InexactComplexnums(TestCase):
    def test_all_random(self):
        for operation in COMPLEX_OPERATIONS:
            for right_generator in numeric_random_generators:

                bound_operation = BoundOperation(random_inexact_complexnum_and_equiv_python_complex,
                                                 right_generator,
                                                 operation)
                for _ in range(0, RANDOM_TRIALS_PER_TEST):
                    with self.subTest():
                        bound_operation.apply_expectation(self.assertComplexAlmostEqual)
