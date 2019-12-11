~/emsdk/emsdk activate latest
  # shellcheck source=/home/scott/emsdk/emsdk_env.sh
source ~/emsdk/emsdk_env.sh
cd wasm_build || exit
GMPDIR=~/opt emconfigure /usr/local/bin/cmake -DBUILD_WASM=True -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE="-s ALLOW_MEMORY_GROWTH=1 -s ENVIRONMENT=node -s STRICT=0 -s STACK_OVERFLOW_CHECK=1 -O3 -DNDEBUG" --with-gmp=${HOME}/opt ..
emmake make -j6
cd ..
