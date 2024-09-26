# Multi Threaded Client Server TCP Chat Application

This is a basic TCP client-server chat application written in C, where multiple clients can connect to the server and exchange messages.


## Features
- Multi-threaded server to handle multiple clients concurrently.
- Simple communication between clients and the server.

## How to Run

### 1. Compile the Server and Client

First, compile the server and client programs. Use `gcc` for compiling, and don’t forget to link the `pthread` library for multi-threading.

```bash
# Compile the server
gcc -o server server.c -pthread

# Compile the client
gcc -o client client.c
```

### 2. Run the Server

Start the server by running the following command:

```bash
./server 8080
```

The server will start listening for connections on port `8080`.

### 3. Run the Client(s)

In a separate terminal, run the client(s) to connect to the server:

```bash
./client 8080
```

You can run multiple clients to simulate different users connecting to the server.
