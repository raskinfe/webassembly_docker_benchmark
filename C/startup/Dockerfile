# Use a minimal base image
FROM gcc:latest

# Install bc
RUN apt-get update && apt-get install -y bc \
&& apt-get install libssl-dev

WORKDIR /


# Copy the C code into the container
COPY startup.c ./c_file.c

# Compile the C code
RUN gcc -o excutable c_file.c

# Command to run when the container starts
CMD ["./excutable"]