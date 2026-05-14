#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port =htons(8080);
    
    bind(server_fd,(struct sockaddr *) &address, sizeof(address));
    
    listen(server_fd, 3);
    
    while(1) {
        // Layer 4 of OLI
        int addrlen = sizeof(address);
        int new_socket_fd = accept(server_fd,(struct sockaddr *) &address,(socklen_t*)&addrlen);

        if (new_socket_fd < 0) continue;
        // Create child process
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed!");
            close(new_socket_fd);
        }

        else if (pid == 0) {
            // we are child process
            close(server_fd);

            char buffer[1024] = {0};
            
            read(new_socket_fd, buffer, sizeof(buffer));
            printf("Response recieved:\n %s", buffer);

            // Layer 7 of OLI
            char *response = "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/plain\r\n"
                    //  Length of Hello World!
                     "Content-Length: 12\r\n"
                     "Connection: close\r\n"
                     "\r\n"
                     "Hello World!";
            write(new_socket_fd, response, strlen(response));
            close(new_socket_fd);
            exit(0);
        }
        close(new_socket_fd);

    }
    return 0;
}