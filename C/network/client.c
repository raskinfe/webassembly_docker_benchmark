#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define MESSAGE "Hello, server!"
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Send a message to the server
        ssize_t bytes_sent = send(client_socket, MESSAGE, strlen(MESSAGE), 0);
        if (bytes_sent == -1) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        // Receive the echoed message from the server
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }

        // Print the received message
        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);

        // Sleep for a short time before the next iteration
        usleep(100000);  // 100 milliseconds
    }

    // Close the client socket
    close(client_socket);

    return 0;
}
