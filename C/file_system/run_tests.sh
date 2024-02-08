#!/bin/bash

# Compile C file with gcc
echo "============================="
echo "Compiling C file with gcc..."
echo "============================="
gcc -o my_c_executable i_o.c -lrt
bash run_multiple.sh ./my_c_executable
rm -rf my_c_executable
echo "============================="
echo -e "\n\n\n"

# Compile to WebAssembly with emcc
echo "============================="
echo "Compiling to WebAssembly with emcc..."
echo "============================="
~/wasi-sdk/wasi-sdk-20.0/bin/clang --sysroot=/home/kinfe/wasi-sdk/wasi-sdk-20.0/share/wasi-sysroot i_o.c -o i_o.wasm -lrt
bash run_multiple.sh wasmtime --dir=. i_o.wasm
rm -rf file.html file.js file.wasm file.data
echo "============================="
echo -e "\n\n\n"

# Run docker-compose build
echo "============================="
echo "Running docker-compose build..."
echo "============================="
docker-compose build -q

# Run docker-compose up
echo "============================="
echo "Running docker-compose up..."
echo "============================="
docker-compose up
echo "============================="
echo -e "\n\n\n"