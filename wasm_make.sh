cp CMakeLists.txt CMakeLists.txt.bak
cp wasmCMakeLists.txt CMakeLists.txt
cd wasm_build
emconfigure /usr/local/bin/cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE="-s USE_BOOST_HEADERS=1 -s ALLOW_MEMORY_GROWTH=1 -s ENVIRONMENT=node -s STRICT=1 -s STACK_OVERFLOW_CHECK=1 -O3" ..
emmake make -j4
cd ..
mv CMakeLists.txt.bak CMakeLists.txt

