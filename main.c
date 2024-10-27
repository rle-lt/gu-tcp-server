#include <stdio.h>      // printf()
#include <sys/socket.h> // socket(), bind(), listen(), etc.
#include <netinet/in.h> // sockaddr_in
#include <string.h>     // strlen()
#include <unistd.h>     // close()

int main(int argc, char *argv[])
{
    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind and listen
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Accept incoming connection
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_socket < 0)
    {
        printf("Connection failed\n");
        return 1;
    }

    // Send message to client
    char *message = "Connection is good!\n";
    int message_length = strlen(message);

    send(client_socket, message, message_length, 0);

    // Receive message from client
    char buffer[32];
    int received_size = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (received_size > 0)
    {
        buffer[received_size] = '\0';
        printf("Received from client: %s\n", buffer);
    }

    // Close sockets
    close(server_socket);
    close(client_socket);
}
