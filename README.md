
# Benchmarks
 - C
 - WASM
 - RUST
 - DOCKER

# Benchmark Implementation and Directory structure

## C Benchmarks

The benchmark test is implemented for cpu_time and performance, memory usage, file system, startup time and security.

for each benchmarks one folder is created. Under each folder respective algorithms are implemented. `shell_scripts`, `Dockerfiles`, and `native C codes` are added to each folder.

* The `shell scripts` are added to compile and run the `native C`, `wasm` and `Dockerfile`.

* The shell script runs each codes 10 time and outputs the average for each.


## Openssl

Emscripten doesn't support openssl library out of the box, so we need to build it for emscripten.
`build_openssl.sh` file holds a script to build openssl for emscripten. It is important to edit the script based on your environment.

## Pre-requisite 

* [Docker desktop / Docker engine](https://www.docker.com/products/docker-desktop/alternatives/)
* [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)
* [wasi-sdk](https://github.com/WebAssembly/wasi-sdk)
* [wasmtime](https://docs.wasmtime.dev/)
* [wasmer](https://wasmer.io/) 
* [docker-compose](https://docs.docker.com/compose/install/standalone/)

## Build scripts

Each directory holds it is own build scripts and `docker-compose.yml` file. And based on the benchmark there is one high level `run_multiple.sh` shell script to run the tests 10 time each and `Dockerfile`. Adjust based on your needs.

