# Use a base image with a C compiler
FROM gcc:latest

ARG C_SOURCE_FILE

# Install bc
RUN apt-get update && apt-get install -y bc \
&& apt-get install libssl-dev

# Set the working directory
WORKDIR /

COPY /cpu/run_multiple.sh .

# Make the script executable
RUN chmod +x run_multiple.sh

# Copy the C code into the container
COPY ${C_SOURCE_FILE} ./c_file.c

# Compile the C code
RUN gcc -o excutable c_file.c  -lssl -lcrypto

# Command to run when the container starts
CMD ["./run_multiple.sh", "./excutable"]
