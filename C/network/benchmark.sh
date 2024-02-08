#!/bin/bash

# Compile C program to native executable
gcc server.c -o native_server
gcc client.c -o native_client

# Compile C program to WebAssembly
emcc server.c -o server.wasm
emcc client.c -o client.wasm

# Build Docker image
docker build -t network-benchmark .

# Run native server and client
./native_server &
SERVER_PID=$!
./native_client &
CLIENT_PID=$!
sleep 5  # Adjust the sleep time as needed

# Measure native memory consumption
echo "Memory consumption for native_server:"
pmap $SERVER_PID | tail -n 1 | awk '{print $2}'

echo "Memory consumption for native_client:"
pmap $CLIENT_PID | tail -n 1 | awk '{print $2}'

# Kill native processes
# Kill native processes if they are still running
if ps -p $SERVER_PID > /dev/null; then
    kill $SERVER_PID
fi
if ps -p $CLIENT_PID > /dev/null; then
    kill $CLIENT_PID
fi


# Run WebAssembly server and client using Wasmer
wasmer run server.wasm &
SERVER_PID=$!
wasmer run client.wasm &
CLIENT_PID=$!
sleep 5  # Adjust the sleep time as needed

# Measure WebAssembly memory consumption
echo "Memory consumption for wasm_server:"
pmap $SERVER_PID | tail -n 1 | awk '{print $2}'

echo "Memory consumption for wasm_client:"
pmap $CLIENT_PID | tail -n 1 | awk '{print $2}'

# Kill wasm processes
# Kill native processes if they are still running
if ps -p $SERVER_PID > /dev/null; then
    kill $SERVER_PID
fi
if ps -p $CLIENT_PID > /dev/null; then
    kill $CLIENT_PID
fi


# Run Docker container
docker run network-benchmark &
CONTAINER_PID=$!
sleep 5  # Adjust the sleep time as needed

# Measure Docker container memory consumption
echo "Memory consumption for Docker container:"
docker stats --no-stream $CONTAINER_PID | tail -n 1 | awk '{print $4}'

# Kill Docker container
docker kill $CONTAINER_PID

# Clean up
rm native_server native_client server.wasm client.wasm
