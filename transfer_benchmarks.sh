ssh-agent || exit
ssh-add ~/.ssh/auth_cade/lab18 || exit
cd ~/CLionProjects/temp/WasmExtendedNumerics || exit
cd cmake-build-release || exit
make -j4 || exit
cd .. || exit
./wasm_make.sh || exit
sftp -b "./transfer_benchmarks.sftp" u0469078@lab1-18.eng.utah.edu
