#!/bin/bash

# Compile C program to native executable
gcc simple_memory.c -o native_executable

# Compile C program to WebAssembly
emcc simple_memory.c -o simple_memory.wasm

# # Build Docker container
# docker-compose build

# Function to run and measure memory consumption
run_and_measure_memory() {
    echo "Memory consumption for $1:"
    
    total_memory=0

    for i in {1..10}; do
        if [[ $1 == *"wasm"* ]]; then
            wasmer run ./$1 > /dev/null 2>&1 &
            sleep 2
            memory=$(free -m | awk '/^Mem:/{print $3}')
        elif [[ $1 == *"docker"* ]]; then
            docker-compose up -d
            sleep 2
            # Extract memory usage without the "KiB" suffix
            memory=$(docker stats --no-stream --format "{{.MemUsage}}" memory-memory-1 | tr -d 'KiB' | awk '{print $1}')
           
        else
            ./$1 > /dev/null 2>&1 &
            sleep 2
            memory=$(free -m | awk '/^Mem:/{print $3}')
        fi

        pid=$!

        # Wait for a few seconds to allow the program to run

        # Measure memory consumption and add it to the total
         echo $memory
        total_memory=$((total_memory + memory))

        # Kill the process or stop Docker container
        if [[ $1 == *"docker"* ]]; then
            docker-compose down
        elif [[ $1 == *"wasm"* ]]; then
            pkill -9 $pid
        else
            pkill -f $pid
        fi

         pkill -f $1
    done

    # Calculate and print the average memory consumption
    pkill -f $1
    average_memory=$((total_memory / 10))
    echo "Average Memory Consumption: $average_memory MiB"
}


run_and_measure_docker() {
    echo "Memory consumption for docker-compose.yml:"
    
    total_memory=0

    for i in {1..10}; do
        docker-compose up -d
        # Extract memory usage without the "KiB" suffix
        memory=$(free -m | grep Mem | awk '{print $3}')
        echo $memory

        # Wait for a few seconds before the next iteration
        sleep 2

        # Add memory usage to the total
        total_memory=$((total_memory + memory))

        # Stop Docker container
        docker-compose down
    done

    # Calculate and print the average memory consumption
    
    average_memory=$((total_memory / 10))
    echo "Average Memory Consumption: $average_memory MiB"
}


# Run and measure memory for native executable
run_and_measure_memory native_executable

# Run and measure memory for WebAssembly module using Wasmer
run_and_measure_memory simple_memory.wasm

# Run and measure memory for Docker container
run_and_measure_docker

# Cleanup
rm -rf simple_memory.wasm native_executable
