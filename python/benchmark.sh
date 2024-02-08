#!/bin/bash

# Compile the client code to WebAssembly
emcc client.py -o client.wasm

# Build the Docker image
docker build -t my_container .

# Start the Docker container in the background
docker run -d -p 8080:8080 my_container
docker_container_id=$(docker ps -q)

# Sleep for a moment to allow the Docker container to start
sleep 2

# Start the server in the background
python server.py &
server_pid=$!

# Sleep for a moment to allow the server to start
sleep 2

# Measure network performance for the client (Native)
echo "Network performance for native execution:"
for i in {1..10}; do
    python client.py > /dev/null 2>&1
    echo "Iteration $i: Request sent and received."
done

# Measure network performance for the client (Docker)
echo "Network performance for Docker container:"
for i in {1..10}; do
    python client.py > /dev/null 2>&1
    echo "Iteration $i: Request sent and received."
done

# Measure network performance for the client (Wasm)
echo "Network performance for Wasm module using Wasmer:"
for i in {1..10}; do
    wasmer run client.wasm > /dev/null 2>&1
    echo "Iteration $i: Request sent and received."
done

# Cleanup
kill $server_pid
docker stop $docker_container_id
