from unittest import TestCase
from test_suites.config_and_defs import RANDOM_TRIALS_PER_TEST, zero, one, negative_one

from test_suites.util_random import random_fixnum, generate_fixnum_a_less_than_b, non_zero_unequal_operands_from, \
    random_fixnum_and_equiv_python_int


class TestNumeric(TestCase):
    def test_fixnum_equality(self):
        self.assertEqual(zero, zero)
        self.assertEqual(one, one)
        self.assertEqual(negative_one, negative_one)
        self.assertNotEqual(zero, one)
        self.assertNotEqual(one, zero)
        self.assertNotEqual(negative_one, one)
        self.assertNotEqual(one, negative_one)
        self.assertNotEqual(zero, negative_one)
        self.assertNotEqual(negative_one, zero)

    def test_fixnum_less_than(self):
        self.assertTrue(zero < one)
        self.assertTrue(negative_one < one)
        self.assertTrue(negative_one < zero)

    def test_fixnum_equals_itself_repeat_n_random(self):
        for _ in range(0, RANDOM_TRIALS_PER_TEST):
            a = random_fixnum()
            with self.subTest(a=a):
                self.assertEqual(a, a, msg="\nNumeric(%s) not equal to itself" % str(a))

    def test_fixnum_less_than_repeat_n_random(self):
        for _ in range(0, RANDOM_TRIALS_PER_TEST):
            a, b = generate_fixnum_a_less_than_b()
            with self.subTest(a=a, b=b):
                result = a < b
                self.assertTrue(result, msg="\nNumeric(%s) not less than Numeric(%s)" % (str(a), str(b)))

    def test_fixnum_division_a_div_b_not_equal_b_div_a_repeat_n_random(self):
        for _ in range(0, RANDOM_TRIALS_PER_TEST):
            a, b = non_zero_unequal_operands_from(random_fixnum)
            with self.subTest(a=a, b=b):
                c = a / b
                d = b / a
                self.assertNotEqual(c, d, msg="\na: %s\nb: %s\na/b: %s\nb/a: %s" % (str(a), str(b), str(c), str(d)))

    def test_fixnum_subtraction_a_sub_b_not_equal_b_sub_a_repeat_n_random(self):
        for _ in range(0, RANDOM_TRIALS_PER_TEST):
            a, b = non_zero_unequal_operands_from(random_fixnum)
            with self.subTest(a=a, b=b):
                c = a - b
                d = b - a
                self.assertNotEqual(c, d, msg="\na: %s\nb: %s\na-b: %s\nb-a: %s" % (str(a), str(b), str(c), str(d)))

    def test_fixnum_addition_correctness_repeat_n_random(self):
        for _ in range(0, RANDOM_TRIALS_PER_TEST):
            a, a_p = random_fixnum_and_equiv_python_int()
            b, b_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, b=b, a_p=a_p, b_p=b_p):
                c = a + b
                c_p = a_p + b_p
                self.assertEqual(c_p, int(str(c)))

    def test_fixnum_subtraction_correctness_repeat_n_random(self):
        for _ in range(0, RANDOM_TRIALS_PER_TEST):
            a, a_p = random_fixnum_and_equiv_python_int()
            b, b_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, b=b, a_p=a_p, b_p=b_p):
                c = a - b
                c_p = a_p - b_p
                self.assertEqual(c_p, int(str(c)))

    def test_fixnum_multiplication_correctness_repeat_n_random(self):
        for _ in range(0, RANDOM_TRIALS_PER_TEST):
            a, a_p = random_fixnum_and_equiv_python_int()
            b, b_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, b=b, a_p=a_p, b_p=b_p):
                c = a * b
                c_p = a_p * b_p
                self.assertEqual(c_p, int(str(c)), msg="\n%s * %s = %s\n%s * %s = %s\n\n" %
                                                       (str(a), str(b), str(c), str(a_p), str(b_p), str(c_p)))

    def test_fixnum_division_correctness_repeat_n_random(self):
        for _ in range(0, RANDOM_TRIALS_PER_TEST):
            a, a_p = random_fixnum_and_equiv_python_int()
            b, b_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, b=b, a_p=a_p, b_p=b_p):
                c = a / b
                c_p = a_p / b_p
                c_numer, c_denom = str(c).split('/')
                self.assertEqual(c_p, int(c_numer) / int(c_denom))


