from unittest import TestCase
from numeric import Numeric
from random import randint, uniform, seed
from functools import partial
from sys import float_info

n = int(1e3)
seed(9439832)
random_float = partial(uniform, -1e12, 1e12)

MIN_FIXNUM_VALUE = -4611686018427387904
MAX_FIXNUM_VALUE = 4611686018427387903

MAX_ARBITRARY_NUM_BITS = 256

zero = Numeric("0")
one = Numeric("1")
negative_one = Numeric("-1")


def random_python_int_outside_fixnum_range():
    candidate = randint(-(1 << MAX_ARBITRARY_NUM_BITS), 1 << MAX_ARBITRARY_NUM_BITS)
    while MIN_FIXNUM_VALUE < candidate < MAX_FIXNUM_VALUE:
        candidate = randint(-(1 << MAX_ARBITRARY_NUM_BITS), 1 << MAX_ARBITRARY_NUM_BITS)
    return candidate


def random_python_int_inside_fixnum_range():
    return randint(MIN_FIXNUM_VALUE, MAX_FIXNUM_VALUE)


def random_fixnum():
    return Numeric(str(random_python_int_inside_fixnum_range()))


def random_fixnum_and_equiv_python_int():
    a = random_python_int_inside_fixnum_range()
    return Numeric(str(a)), a


def random_inexact_complexnum():
    return Numeric(random_float(), random_float())


def random_inexact_complexnum_and_equiv_python_floats():
    real = random_float()
    imaginary = random_float()
    return Numeric(real, imaginary), real, imaginary


def random_bignum():
    return Numeric(str(random_python_int_outside_fixnum_range()))


def random_ratnum():
    return Numeric(str(random_python_int_outside_fixnum_range()), str(random_python_int_outside_fixnum_range()))


def random_exact_complexnum():
    return Numeric(str(random_python_int_outside_fixnum_range()), str(random_python_int_outside_fixnum_range()),
                   str(random_python_int_outside_fixnum_range()), str(random_python_int_outside_fixnum_range()))


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

    def test_fixnum_equality_random_repeat_n(self):
        for _ in range(0, n):
            a = random_fixnum()
            with self.subTest(a=a):
                self.assertEqual(a, a, msg="\nNumeric(%s) not equal to itself" % str(a))

    def test_fixnum_less_than_random_repeat_n(self):
        for _ in range(0, n):
            a, b = generate_fixnum_a_less_than_b()
            with self.subTest(a=a, b=b):
                result = a < b
                self.assertTrue(result, msg="\nNumeric(%s) not less than Numeric(%s)" % (str(a), str(b)))

    def test_division_asymmetry_fixnum_random_repeat_n(self):
        for _ in range(0, n):
            a, b = non_zero_unequal_operands_from(random_fixnum)
            with self.subTest(a=a, b=b):
                c = a / b
                d = b / a
                self.assertNotEqual(c, d, msg="\na: %s\nb: %s\na/b: %s\nb/a: %s" % (str(a), str(b), str(c), str(d)))

    def test_subtraction_asymmetry_fixnum_random_repeat_n(self):
        for _ in range(0, n):
            a, b = non_zero_unequal_operands_from(random_fixnum)
            with self.subTest(a=a, b=b):
                c = a - b
                d = b - a
                self.assertNotEqual(c, d, msg="\na: %s\nb: %s\na-b: %s\nb-a: %s" % (str(a), str(b), str(c), str(d)))

    def test_addition_correctness_fixnum_random_repeat_n(self):
        for _ in range(0, n):
            a, a_p = random_fixnum_and_equiv_python_int()
            b, b_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, b=b, a_p=a_p, b_p=b_p):
                c = a + b
                c_p = a_p + b_p
                self.assertEqual(c_p, int(str(c)))

    def test_subtraction_correctness_fixnum_random_repeat_n(self):
        for _ in range(0, n):
            a, a_p = random_fixnum_and_equiv_python_int()
            b, b_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, b=b, a_p=a_p, b_p=b_p):
                c = a - b
                c_p = a_p - b_p
                self.assertEqual(c_p, int(str(c)))

    def test_multiplication_correctness_fixnum_random_repeat_n(self):
        for _ in range(0, n):
            a, a_p = random_fixnum_and_equiv_python_int()
            b, b_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, b=b, a_p=a_p, b_p=b_p):
                c = a * b
                c_p = a_p * b_p
                self.assertEqual(c_p, int(str(c)), msg="\n%s * %s = %s\n%s * %s = %s\n\n" %
                                                       (str(a), str(b), str(c), str(a_p), str(b_p), str(c_p)))

    def test_division_correctness_fixnum_random_repeat_n(self):
        for _ in range(0, n):
            a, a_p = random_fixnum_and_equiv_python_int()
            b, b_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, b=b, a_p=a_p, b_p=b_p):
                c = a / b
                c_p = a_p / b_p
                c_numer, c_denom = str(c).split('/')
                self.assertEqual(c_p, int(c_numer) / int(c_denom))

    def test_division_correctness_fixnum_inexact_complexnum_division_repeat_n(self):
        for _ in range(0, 1):
            a, a_real, a_imaginary = random_inexact_complexnum_and_equiv_python_floats()
            d = complex(a_real, a_imaginary)
            a = a / Numeric("1734")
            d = d / 17340000000
            b, b_real, b_imaginary = random_inexact_complexnum_and_equiv_python_floats()
            c, c_p = random_fixnum_and_equiv_python_int()
            with self.subTest(a=a, a_real=a_real, a_imaginary=a_imaginary):
                z, i = str(a).split(' ')
                i = i.rstrip('i')

                self.assertAlmostEqual(float(z), d.real, delta=0.5,
                                       msg="\n%s %s %s\n%s\n%s %s\n\n" %
                                           (str(a), str(a_real), str(a_imaginary), str(d), str(z), str(i)))
                self.assertAlmostEqual(float(i), d.imag, delta=0.5,
                                       msg="\n%s %s %s\n%s\n%s %s\n\n" %
                                           (str(a), str(a_real), str(a_imaginary), str(d), str(z), str(i)))
