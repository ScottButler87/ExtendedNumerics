~/emsdk/emsdk activate latest
  # shellcheck source=/home/scott/emsdk/emsdk_env.sh
source ~/emsdk/emsdk_env.sh
cp CMakeLists.txt CMakeLists.txt.bak
cp wasmCMakeLists.txt CMakeLists.txt
cd wasm_build || exit
emconfigure /usr/local/bin/cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE="-s USE_BOOST_HEADERS=1 -s ALLOW_MEMORY_GROWTH=1 -s ENVIRONMENT=node -s STRICT=0 -s STACK_OVERFLOW_CHECK=1 -O3 -DNDEBUG" ..
emmake make -j6
cd ..
mv CMakeLists.txt.bak CMakeLists.txt

