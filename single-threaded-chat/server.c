#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080      // Port the server will listen on
#define BUFFER_SIZE 1024  // Size of the message buffer

int main() {
    int server_fd, new_socket; //creating a server file descriptor and new socket
    struct sockaddr_in address; //Structure for handling internet addresses (see doc)
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "Hello from server";

    // Step 1: Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Bind the socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    address.sin_port = htons(PORT);       // Host to network byte order for the port number

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Step 3: Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Step 4: Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    // Step 5: Communication loop
    while (1) {
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) {
            printf("Client disconnected or error occurred\n");
            break;
        }
        printf("Received from client: %s\n", buffer);
        
        // echo the response to the client
        send(new_socket, buffer, strlen(buffer), 0);
        printf("message sent\n");

        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);
    }

    // Step 6: Close the socket
    close(new_socket);
    close(server_fd);

    printf("Server closed\n");
    return 0;
}
