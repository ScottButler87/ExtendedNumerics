from unittest import TestCase
from typing import Union, Callable, Any, List, Optional
from functools import partial
from numeric import Numeric

from test_suites.config_and_defs import SUPPRESS_CONVERSION_FAILURES, RANDOM_TRIALS_PER_TEST, inexact_expectation, \
    PRINT_DEBUG_INFO
from test_suites.util_representation import get_transformation_dictionary
from test_suites.util_types import PyVal, RandomGenerator
from test_suites.util_random import ALL_RANDOM_NUMERIC_AND_PYVAL_GENERATORS


def generic_error_message(operation_char: str):
    return lambda left, right, expected, got:\
        'Expected %s %s %s = %s, got %s' % (left, operation_char, right, expected, got)


def verbose_wrapper(assertion: Callable[[Any, Any, str], None]):
    def wrapper(*args, **kwargs):
        for arg in args:
            print(arg)
        for k, v in kwargs.items():
            print("%s: %s" % (k, v))
        assertion(*args)
    return wrapper


class Operation:
    def __init__(self,
                 operation_name: str,
                 bifunc: Union[Callable[[Numeric, Numeric], Numeric], Callable[[PyVal, PyVal], PyVal]],
                 error_message_generator: Callable[[Numeric, Numeric, PyVal, PyVal], str]):
        self.operation_name = operation_name
        self.bifunc = bifunc
        self.error_message_generator = error_message_generator


class BoundOperation(Operation):
    def __init__(self,
                 left_generator: RandomGenerator,
                 right_generator: RandomGenerator,
                 operation: Operation):
        super().__init__(operation.operation_name, operation.bifunc, operation.error_message_generator)
        self.left_generator = left_generator
        self.right_generator = right_generator
        self.transformations = get_transformation_dictionary()
        self.suppression_count = 0

    def dump_run_info(self, left, py_left, right, py_right, result, expected, transform: Callable[..., Any] = None):
        print('%12s %s' % ('Operation:', self.operation_name))
        if transform is not None and transform.__name__ is not None:
            print('%12s %s' % ('Transform op:', transform.__name__))
        print('%12s %s' % ('left:', left))
        print('%12s %s' % ('py_left:', py_left))
        print('%12s %s' % ('right:', right))
        print('%12s %s' % ('py_right:', py_right))
        print('%12s %s' % ('result:', result))
        print('%12s %s\n' % ('expected:', expected))

    def apply_expectations(self, expectation: Callable[..., None], inexact_expectation_: Callable[..., None]):
        left, py_left = self.left_generator()
        right, py_right = self.right_generator()
        result = self.bifunc(left, right)
        expected = self.bifunc(py_left, py_right)
        comparable = result
        if isinstance(result, Numeric):
            transform = self.transformations[result.type()]
            try:
                comparable = transform(result)
            except RuntimeError:
                if not SUPPRESS_CONVERSION_FAILURES:
                    print("Conversion failure --")
                    self.dump_run_info(left, py_left, right, py_right, result, expected, transform)
                self.suppression_count += 1
                return
        error_message: str = self.error_message_generator(left, right, expected, comparable)
        if isinstance(expected, float):
            comparable = float(comparable)
            to_expect = inexact_expectation_
        elif isinstance(expected, complex):
            comparable = complex(float(comparable.real), float(comparable.imag))
            to_expect = inexact_expectation_
        else:
            if PRINT_DEBUG_INFO:
                self.dump_run_info(left, py_left, right, py_right, comparable, expected)
            to_expect = expectation
        try:
            to_expect(comparable, expected, msg=error_message)
        except AssertionError:
            self.dump_run_info(left, py_left, right, py_right, comparable, expected, self.transformations[result.type()])
            raise


class CaseStudy:
    def __init__(self, host: TestCase, left_generator: RandomGenerator):
        self.___left_generator = left_generator
        self.___host = host
        if 'complex' in left_generator.__name__:
            self.___expectation = host.assertComplexEqual
            self.___inexact_expectation = host.assertComplexAlmostEqual
        else:
            self.___expectation = host.assertEqual
            self.___inexact_expectation = partial(inexact_expectation, host)

    def test_all_operations_with_random_operands_n_times(self, n=RANDOM_TRIALS_PER_TEST):
        for operation in OPERATIONS:
            for right_generator in ALL_RANDOM_NUMERIC_AND_PYVAL_GENERATORS:
                bound_operation = BoundOperation(self.___left_generator,
                                                 right_generator,
                                                 operation)
                # skip less than for complex, it is not defined for them
                if operation == LT and ('complex' in right_generator.__name__ or 'complex' in self.___left_generator.__name__):
                    continue
                for _ in range(0, n):
                    with self.___host.subTest():
                        bound_operation.apply_expectations(self.___expectation, self.___inexact_expectation)
                if bound_operation.suppression_count != 0:
                    print("Conversion failures suppressed: %d" % bound_operation.suppression_count)


ADD = Operation('addition', lambda left, right: left + right, generic_error_message('+'))
SUB = Operation('subtraction', lambda left, right: left - right, generic_error_message('-'))
MULT = Operation('multiplication', lambda left, right: left * right, generic_error_message('*'))
DIV = Operation('division', lambda left, right: left / right, generic_error_message('/'))
EQ = Operation('equals', lambda left, right: left == right, generic_error_message('=='))
NEQ = Operation('not equals', lambda left, right: left != right, generic_error_message('!='))
LT = Operation('less than', lambda left, right: left < right, generic_error_message('<'))

OPERATIONS: List[Operation] = [
    ADD,
    SUB,
    MULT,
    DIV,
    EQ,
    NEQ,
    LT
]
