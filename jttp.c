#include "jttp.h"

int respondWithHTML(int clientSocket) {
    FILE *htmlFile = fopen(HTML_FILE_PATH, "r");
    if (htmlFile == NULL) {
        printf("Failed to open HTML file.\n");
        return 0;
    }

    char responseBuffer[1024];
    size_t bytesRead;

    // Send the response header
    write(clientSocket, RESPONSE_HEADER, strlen(RESPONSE_HEADER));

    // Read and send the HTML file contents
    while ((bytesRead = fread(responseBuffer, 1, sizeof(responseBuffer), htmlFile)) > 0) {
        write(clientSocket, responseBuffer, bytesRead);
    }

    fclose(htmlFile);
    return 1;
}

int main(int argc, char *argv[]) {
    const int PORT = 8080; // Port to listen on

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
    if (listen_result < 0) {
        perror("Could not listen on socket ");
        exit(EXIT_FAILURE);
    }

    // Accept a connection
    while (1) {
        printf("\n***** Waiting for a new connection *****\n\n");
        int client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client_fd < 0) {
            perror("Could not accept connection");
            exit(EXIT_FAILURE);
        }

        // Respond with HTML
        if (respondWithHTML(client_fd) == 1) {
            printf("***** HTML sent *****\n");
        } else {
            printf("***** Failed to send HTML *****\n");
        }

        close(client_fd); // Close the connection
    }
    return 0;
}
