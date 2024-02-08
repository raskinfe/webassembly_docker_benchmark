// socket_benchmark_latency.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

#define PORT 8080
#define MESSAGE_SIZE 1024

void error(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[MESSAGE_SIZE];
    struct timeval start_time, end_time;

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        error("Error creating socket");

    // Setup server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        error("Error binding");

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1)
        error("Error listening");

    printf("Server listening on port %d...\n", PORT);

    // Accept connection from client
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) == -1)
        error("Error accepting connection");

    printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

    // Receive message from client
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);

    // Measure start time
    gettimeofday(&start_time, NULL);

    // Send the message back to the client
    send(client_socket, buffer, sizeof(buffer), 0);

    // Measure end time
    gettimeofday(&end_time, NULL);

    // Calculate latency in microseconds
    long latency = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

    printf("Latency: %ld microseconds\n", latency);

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
