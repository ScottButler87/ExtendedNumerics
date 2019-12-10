from fractions import Fraction
from typing import Union, Callable, Any, List
from numeric import Numeric
from test_suites.config_and_defs import SUPPRESS_CONVERSION_FAILURES
from test_suites.util_representation import get_transformation_dictionary

from test_suites.util_types import PyVal, RandomGenerator, ExactComplex


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

    def apply_expectation(self, expectation: Callable[..., None]):
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
                    print('%12s %s' % ('Operation:', self.operation_name))
                    print('%12s %s' % ('left:', left))
                    print('%12s %s' % ('py_left:', py_left))
                    print('%12s %s' % ('right:', right))
                    print('%12s %s' % ('py_right:', py_right))
                    print('%12s %s' % ('result:', result))
                    print('%12s %s' % ('expected:', expected))
                    print('%12s %s\n' % ('Transform op:', transform.__name__))
                self.suppression_count += 1
                return
        error_message: str = self.error_message_generator(left, right, expected, comparable)
        if isinstance(expected, float) or isinstance(expected, complex):
            if isinstance(comparable, Fraction) and self.operation_name is 'division':
                comparable = float(comparable)

        elif isinstance(expected, complex) and isinstance(comparable, ExactComplex):
            comparable = complex(float(comparable.real), float(comparable.imag))
        # try:
        expectation(comparable, expected, msg=error_message)
        # except AssertionError:
        #     print('%12s %s' % ('Operation:', self.operation_name))
        #     print('%12s %s' % ('left:', left))
        #     print('%12s %s' % ('py_left:', py_left))
        #     print('%12s %s' % ('right:', right))
        #     print('%12s %s' % ('py_right:', py_right))
        #     print('%12s %s' % ('comparable:', comparable))
        #     print('%12s %s\n' % ('expected:', expected))


ADD = Operation('addition', lambda left, right: left + right, generic_error_message('+'))
SUB = Operation('subtraction', lambda left, right: left - right, generic_error_message('-'))
MULT = Operation('multiplication', lambda left, right: left * right, generic_error_message('*'))
DIV = Operation('division', lambda left, right: left / right, generic_error_message('/'))
EQ = Operation('equals', lambda left, right: left == right, generic_error_message('=='))
NEQ = Operation('not equals', lambda left, right: left != right, generic_error_message('!='))
LT = Operation('less than', lambda left, right: left < right, generic_error_message('<'))

COMPLEX_OPERATIONS: List[Operation] = [
    ADD,
    SUB,
    MULT,
    DIV,
    EQ,
    NEQ
]

OPERATIONS: List[Operation] = [
    *COMPLEX_OPERATIONS,
    # LT
]