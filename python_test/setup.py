from distutils.core import setup, Extension

name = "Numeric"

version = "1.0"

ext_modules = Extension(name="_numeric",
                        sources=["../src/ExtendedNumerics.cpp", "ExtendedNumerics.i"],
                        swig_opts=["-modern", "-py3", "-c++", "-addextern"],
                        extra_compile_args=["-std=c++14", "-lstdc++", "-O3"],
                        include_dirs=["../include", "/usr/include/python3.6"])

setup(name=name, version=version, ext_modules=[ext_modules])
