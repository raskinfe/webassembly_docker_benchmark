#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <wasmer or executable> [wasm_file or additional_arguments]"
    exit 1
fi

if [ "$1" == "wasmer" ]; then
    if [ "$#" -lt 2 ]; then
        echo "Usage: $0 wasmer <wasm_file> [additional_arguments]"
        exit 1
    fi

    executable="wasmer"
    wasm_file=$2
    shift 2  # Remove "wasmer" and the wasm file from the arguments
else
    executable=$1
    wasm_file=""  # No wasm file specified
    shift  # Remove the executable from the arguments
fi

NUM_RUNS=10
total_cpu_time=0.0

for ((run=1; run<=$NUM_RUNS; run++)); do
    if [ -n "$wasm_file" ]; then
        result=$("$executable" "$wasm_file" "$@")
    else
        result=$("$executable" "$@")
    fi

    # Extract the last word from the result if available
    elapsed_time=$(echo "$result" | awk '{print $(NF-1)}')

    # Check if elapsed_time is a non-empty string
    if [ -n "$elapsed_time" ]; then
        total_cpu_time=$(echo "$total_cpu_time + $elapsed_time" | bc)
        echo "Run $run - $result"
    else
        echo "Run $run - Unable to extract elapsed time from: $result"
    fi
done

if [ "$NUM_RUNS" -gt 0 ]; then
    average_cpu_time=$(echo "scale=9; $total_cpu_time / $NUM_RUNS" | bc)
    echo "Average CPU time over $NUM_RUNS runs: $average_cpu_time seconds"
else
    echo "No runs performed."
fi
