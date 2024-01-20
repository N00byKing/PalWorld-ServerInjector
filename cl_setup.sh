export PATH=~/Desktop/msvc-wine/msstuff/bin/x64:$PATH
export CC=clang-cl
export CXX=clang-cl

export BIN=~/Desktop/msvc-wine/msstuff/bin/x64/

source ~/Desktop/msvc-wine/msvcenv-native.sh

cmake -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
