#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080         // Port to connect to the server
#define BUFFER_SIZE 1024   // Size of the message buffer

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    // Step 1: Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;          // IPv4
    serv_addr.sin_port = htons(PORT);        // Port number

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // Step 2: Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    printf("Connected to server\n");

    // Step 3: Communication loop
    while (1) {
        // Get input from the user
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send the message to the server
        send(sock, buffer, strlen(buffer), 0);
        printf("Message sent\n");

        // Clear the buffer for the next message
        memset(buffer, 0, BUFFER_SIZE);

        // Receive the response from the server
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread <= 0) {
            printf("Server disconnected or error occurred\n");
            break;
        }
        printf("Received from server: %s\n", buffer);
    }

    // Step 4: Close the socket
    close(sock);
    printf("Client closed\n");
    
    return 0;
}
