
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    // creates socket file descriptor
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT); // host to network -- coverts the ending of the given integer
    const int addrlen = sizeof(address);
    // binding
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // listening on server socket with backlog size 3.
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Listen on %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    // accepting client
    // accept returns client socket and fills given address and addrlen with client address information.
    int client_socket, valread;
    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Hello client %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    // reads a buffer with maximum size 1024 from socket.
    valread = read(client_socket, buffer, 1024);
    if (valread < 0)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("(s = %d) %s\n", valread, buffer);
    // writes to client socket
    send(client_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    return 0;
}