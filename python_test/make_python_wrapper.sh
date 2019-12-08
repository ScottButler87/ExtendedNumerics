#!/bin/bash
rm -rf extended_numerics.py ExtendedNumerics_wrap.cpp numeric.py _numeric*.so __pycache__/ build
python3 setup.py build_ext --inplace
