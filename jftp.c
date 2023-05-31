#include "jttp.h"

int main(int argc, char *argv[]) {

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create a socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Bind to a port
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int bind_result = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (bind_result < 0) {
        perror("Could not bind to port");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    const int backlog = 10; // this is the max no of connections to hold in queue
    int listen_result = listen(server_fd, backlog);
    if (listen_result < 0){
        perror("Could not listen on socket ");
        exit(EXIT_FAILURE);
    }

    // Accept a connection
    while(1){
        printf("\n***** Waiting for a new connection *****\n\n");
        int client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("Could not accept connection");
            exit(EXIT_FAILURE);
        }

        // Read from the socket
        char buffer[buffsiz];
        memset(buffer, 0, buffsiz);
        long valread = read(client_fd, buffer, buffsiz);
        printf("Received %ld bytes\n", valread);
        printf("Message: %s\n", buffer);

        close(client_fd); // Close the connection
    }
    return 0;
}
