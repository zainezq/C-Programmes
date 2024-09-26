#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080      // Port the server will listen on
#define BUFFER_SIZE 1024  // Size of the message buffer

void *client_handler(void *socket_desc) {
    int client_sock = *(int*)socket_desc;
    char buffer[BUFFER_SIZE];

    // Communication loop
    while (1) {
        int read_size = recv(client_sock, buffer, BUFFER_SIZE, 0);
        if (read_size <= 0) {
            printf("Client disconnected or error occurred\n");
            break;
        }

        // Null-terminate the received string
        buffer[read_size] = '\0';
        printf("Received from client: %s\n", buffer);

        // Send a response to the client
        send(client_sock, buffer, strlen(buffer), 0);

        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);
    }

    // Close the client socket
    close(client_sock);
    free(socket_desc);

    return NULL;
}


int main(int argc, char *argv[]) {
  int port;
  if(argc == 2) {
    port = atoi(argv[1]);
    if (port <= 49151 && port >= 1024){
    } else {
      printf("Incorrect port number provided");
      return 1;
    }
  } else if (argc < 2){
    printf("One arguement expected\n");
    return 1;
  } else {
    printf("too many arguments supplied\n");
    return 1;
  }

  int server_fd, client_sock, *new_sock;
  struct sockaddr_in server, client;
  int addr_len = sizeof(struct sockaddr_in);
  
  // Step 1: Create socket file descriptor
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }
  
  // Step 2: Bind the socket to the port
  
  
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
  server.sin_port = htons(port);       // Host to network byte order for the port number

  if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }
  
  // Step 3: Start listening for incoming connections
  if (listen(server_fd, 3) < 0) {
    perror("Listen failed");
        exit(EXIT_FAILURE);
  }
  
  printf("Server listening on port %d\n", port);
  
  // Step 4: Accept incoming connection

  while ((client_sock = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&addr_len))) {
    printf("Connection accepted\n");
    
    // Step 6: Create a thread for each client
    pthread_t client_thread;
    new_sock = malloc(1);
    *new_sock = client_sock;
    
    if (pthread_create(&client_thread, NULL, client_handler, (void*) new_sock) < 0) {
      perror("Could not create thread");
      exit(EXIT_FAILURE);
    }
    
    printf("Handler assigned to client\n");
  }
  if (client_sock < 0) {
    perror("Accept failed");
    exit(EXIT_FAILURE);
  }
  return 0;
}
