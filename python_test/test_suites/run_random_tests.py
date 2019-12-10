from unittest import TestCase

from test_suites.util_operations import CaseStudy
from test_suites.util_random import random_fixnum_and_equiv_python_int,\
    random_bignum_and_equiv_python_int,\
    random_ratnum_and_equiv_python_fraction,\
    random_inexact_complexnum_and_equiv_python_complex,\
    random_exact_complexnum_and_equiv_python_exactcomplex


class FixnumRandomTests(TestCase):
    def runTest(self):
        case_study = CaseStudy(self, random_fixnum_and_equiv_python_int)
        case_study.test_all_operations_with_random_operands_n_times()


class BignumRandomTests(TestCase):
    def runTest(self):
        case_study = CaseStudy(self, random_bignum_and_equiv_python_int)
        case_study.test_all_operations_with_random_operands_n_times()


class RatnumRandomTests(TestCase):
    def runTest(self):
        case_study = CaseStudy(self, random_ratnum_and_equiv_python_fraction)
        case_study.test_all_operations_with_random_operands_n_times()


class ExactComplexnumRandomTests(TestCase):
    def runTest(self):
        case_study = CaseStudy(self, random_exact_complexnum_and_equiv_python_exactcomplex)
        case_study.test_all_operations_with_random_operands_n_times()


class InexactComplexnumRandomTests(TestCase):
    def runTest(self):
        case_study = CaseStudy(self, random_inexact_complexnum_and_equiv_python_complex)
        case_study.test_all_operations_with_random_operands_n_times()
