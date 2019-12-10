# from unittest import TestCase
# from functools import partial
#
# from test_suites.config_and_defs import RANDOM_TRIALS_PER_TEST, inexact_expectation
#
# from test_suites.util_random import\
#     random_inexact_complexnum_and_equiv_python_complex,\
#     random_fixnum_and_equiv_python_int,\
#     random_bignum_and_equiv_python_int,\
#     random_ratnum_and_equiv_python_fraction,\
#     random_exact_complexnum_and_equiv_python_exactcomplex
#
# from test_suites.util_operations import BoundOperation, OPERATIONS
#
# numeric_random_generators = [
#     random_fixnum_and_equiv_python_int,
#     random_bignum_and_equiv_python_int,
#     random_ratnum_and_equiv_python_fraction,
#     random_exact_complexnum_and_equiv_python_exactcomplex,
#     random_inexact_complexnum_and_equiv_python_complex
# ]
#
#
# class Ratnums(TestCase):
#     def test_all_random(self):
#         for operation in OPERATIONS:
#             for right_generator in numeric_random_generators:
#                 if 'inexact' in right_generator.__name__:
#                     expectation = partial(inexact_expectation, self)
#                 else:
#                     expectation = self.assertEqual
#                 bound_operation = BoundOperation(random_ratnum_and_equiv_python_fraction,
#                                                  right_generator,
#                                                  operation)
#                 for _ in range(0, RANDOM_TRIALS_PER_TEST):
#                     with self.subTest():
#                         bound_operation.apply_expectation(expectation)
#                 if bound_operation.suppression_count != 0:
#                     print("Conversion failures suppressed: %d" % bound_operation.suppression_count)
