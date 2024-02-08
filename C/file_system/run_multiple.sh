#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <executable or wasmer> [wasm_file or additional_arguments]"
    exit 1
fi

if [ "$1" == "wasmtime" ]; then
    if [ "$#" -lt 2 ]; then
        echo "Usage: $0 wasmtime <wasm_file> [additional_arguments]"
        exit 1
    fi

    executable="wasmtime"
    wasm_file=$2
    shift 2  # Remove "wasmer" and the wasm file from the arguments
else
    executable=$1
    wasm_file=""  # No wasm file specified
    shift  # Remove the executable from the arguments
fi

NUM_RUNS=10
total_write_time=0.0
total_read_time=0.0

for ((run=1; run<=$NUM_RUNS; run++)); do
    result=$("$executable" "$wasm_file" "$@")

    # Extract write and read times from the output
    write_time=$(echo "$result" | awk '/Write Time:/ {print $(NF-1)}')
    read_time=$(echo "$result" | awk '/Read Time:/ {print $(NF-1)}')

    # Check if times are non-empty strings
    if [ -n "$write_time" ] && [ -n "$read_time" ]; then
        total_write_time=$(echo "$total_write_time + $write_time" | bc)
        total_read_time=$(echo "$total_read_time + $read_time" | bc)
        echo "Run $run - $result"
    else
        echo "Run $run - Warning: Unable to extract times from: $result"
    fi
done

if [ "$NUM_RUNS" -gt 0 ]; then
    average_write_time=$(echo "scale=9; $total_write_time / $NUM_RUNS" | bc)
    average_read_time=$(echo "scale=9; $total_read_time / $NUM_RUNS" | bc)
    echo "Average Write Time over $NUM_RUNS runs: $average_write_time seconds"
    echo "Average Read Time over $NUM_RUNS runs: $average_read_time seconds"
else
    echo "No runs performed."
fi
