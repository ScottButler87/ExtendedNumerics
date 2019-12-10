from distutils.core import setup, Extension

name = "Numeric"

version = "1.0"

ext_modules = Extension(name="_numeric",
                        sources=["../src/ExtendedNumerics.cpp",
                                 "../src/BignumInternal.cpp",
                                 "../src/RatnumInternal.cpp",
                                 "../src/ExactComplexnumInternal.cpp",
                                 "../src/InexactComplexnumInternal.cpp",
                                 "../src/DynamicDoubleDispatch.cpp",
                                 "ExtendedNumerics.i"],
                        swig_opts=["-modern", "-py3", "-c++", "-addextern"],
                        extra_compile_args=["-std=c++14", "-lstdc++", "-O3"],
                        include_dirs=["../include"])

setup(name=name, version=version, ext_modules=[ext_modules])
