#!/bin/bash

# Compile C file with gcc
echo "============================="
echo "Compiling C file with gcc..."
echo "============================="
gcc -o my_c_executable aes.c -I/usr/include/openssl -L/usr/bin/openssl -lssl -lcrypto -w
bash ../run_multiple.sh ./my_c_executable
rm -rf my_c_executable
echo "============================="
echo -e "\n\n\n"

# Compile to WebAssembly with emcc
echo "============================="
echo "Compiling to WebAssembly with emcc..."
echo "============================="
emcc aes.c -o my_c_wasm.wasm -I/home/kinfe/openssl/build/include/ -L/home/kinfe/openssl/build/lib -lssl -lcrypto
bash ../run_multiple.sh wasmer my_c_wasm.wasm
rm -rf my_c_wasm.wasm
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