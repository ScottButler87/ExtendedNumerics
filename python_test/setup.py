from distutils.core import setup, Extension

name = "Numeric"

version = "1.0"

ext_modules = Extension(name="_numeric",
                        sources=[
                            "../src/BignumInternal.cpp",
                             "../src/DynamicDoubleDispatch.cpp",
                             "../src/ExactComplexnumInternal.cpp",
                             "../src/ExtendedNumerics.cpp",
                             "../src/InexactComplexnumInternal.cpp",
                             "../src/Numeric.cpp",
                             "../src/RatnumInternal.cpp",
                             "ExtendedNumerics.i"],
                        swig_opts=["-modern", "-py3", "-c++", "-addextern"],
                        extra_compile_args=["-std=c++14", "-lstdc++", "-O3"],
                        extra_link_args=["-O3"],
                        include_dirs=["../include", "/usr/local/include", "/usr/include/x86_64-linux-gnu"],
                        library_dirs=["/usr/lib/x86_64-linux-gnu"],
                        libraries=["gmp"])

setup(name=name, version=version, ext_modules=[ext_modules], requires=['nose'])
