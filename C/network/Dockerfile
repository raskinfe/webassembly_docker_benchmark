# Use a base image with a C compiler
FROM gcc:latest


# Install bc
RUN apt-get update && apt-get install -y bc \
&& apt-get install libssl-dev

# Set the working directory
WORKDIR /

# Copy the C code into the container
COPY server.c ./server.c
COPY client.c ./client.c

# Compile the C code
RUN gcc -o server server.c
RUN gcc -o client client.c

# Command to run when the container starts
CMD ["./server", "./client"]
