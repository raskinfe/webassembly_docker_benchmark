#!/bin/bash

# Compile C program to native executable
gcc startup.c -o native_executable

# Compile C program to WebAssembly
emcc startup.c -o startup.wasm

# Function to measure startup time
measure_startup_time() {
    total_time=0

    for i in {1..10}; do
        start_time=$(date +%s%N)
        ./$1 > /dev/null
        end_time=$(date +%s%N)
        elapsed_time=$((end_time - start_time))
        echo "$i: $elapsed_time"
        total_time=$((total_time + elapsed_time))
    done

    average_time=$((total_time / 10))
    echo "Average Startup Time for $1: $average_time nanoseconds"
}

# Function to measure Docker container startup time
measure_docker_startup_time() {
    total_time=0

    for i in {1..10}; do
        start_time=$(date +%s%N)
        docker-compose up -d
        end_time=$(date +%s%N)
        elapsed_time=$((end_time - start_time))
        echo "$i: $elapsed_time"
        total_time=$((total_time + elapsed_time))

        docker-compose down 
    done

    average_time=$((total_time / 10))
    echo "Average Startup Time for Docker container: $average_time nanoseconds"
}

# Function to measure WebAssembly module startup time using Wasmer
measure_wasm_startup_time() {
    total_time=0

    for i in {1..10}; do
        start_time=$(date +%s%N)
        wasmer run startup.wasm > /dev/null
        end_time=$(date +%s%N)
        elapsed_time=$((end_time - start_time))
        echo "$i: $elapsed_time"
        total_time=$((total_time + elapsed_time))
    done

    average_time=$((total_time / 10))
    echo "Average Startup Time for WebAssembly (Wasmer): $average_time nanoseconds"
}

# Measure startup time for native executable
measure_startup_time native_executable

# Measure startup time for WebAssembly using Wasmer
measure_wasm_startup_time

# Measure startup time for Docker container
measure_docker_startup_time

# Cleanup
rm -f native_executable startup.wasm
