# Use a base image with a C compiler
FROM gcc:latest

# Install bc
RUN apt-get update && apt-get install -y bc \
&& apt-get install libssl-dev

COPY simple_memory.c /app/simple_memory.c

# Set the working directory
WORKDIR /app

# Compile the C code
RUN gcc -o native_executable simple_memory.c

CMD ["./native_executable"]
