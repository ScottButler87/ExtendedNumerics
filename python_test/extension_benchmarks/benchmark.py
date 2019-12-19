import timeit

from test_suites.util_operations import ARITHMETIC_OPERATIONS

from test_suites.util_random import ALL_RANDOM_NUMERIC_GENERATORS_AND_NAMES

repetitions_to_time = 100000

left = None
right = None
operation = lambda x, y: None


def run_operation():
    global left
    global right
    global operation
    operation(left, right)

if __name__ == "__main__":
    for i in range(0, 10000):
        print('Result set %s' % i)
        print("%s,%s,%s,%s,%s,%s" % ('operation', 'left_operand', 'right_operand', 'repetitions', 'extension_seconds', 'python_seconds'))
        for oper in ARITHMETIC_OPERATIONS:
            for left_gen, left_type in ALL_RANDOM_NUMERIC_GENERATORS_AND_NAMES:
                for right_gen, right_type in ALL_RANDOM_NUMERIC_GENERATORS_AND_NAMES:
                    left, py_left = left_gen()
                    right, py_right = right_gen()
                    operation = oper.bifunc
                    print("%s,%s,%s,%s,%s,%s,%s" % (oper.operation_name, left_type, type(py_left).__name__, right_type, type(py_right).__name__, repetitions_to_time,
                        timeit.timeit('run_operation()', number=repetitions_to_time, setup="from __main__ import run_operation")), end='')
                    left = py_left
                    right = py_right
                    print(',%s' % timeit.timeit('run_operation()', number=repetitions_to_time, setup="from __main__ import run_operation"), flush=True)
        print()

