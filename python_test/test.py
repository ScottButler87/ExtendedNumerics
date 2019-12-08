from numeric import Numeric, print_numeric, int_div, int_sub, int_add
from random import random, randint

a = Numeric("12", "5")
b = Numeric("2")
c = Numeric("6", "5")
d = Numeric("5", "6")

assert(a/b == c)

assert(b/a == d)
