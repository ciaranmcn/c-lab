#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
int main() {
    struct sockaddr_in server_addr;
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct hostent *server = gethostbyname("www.google.com");
    if (server == NULL) {
        printf("couln't find hostname");
        return 1;
    }
    if (socket_fd < 0) {
        return 1;
    }

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // copying h_addr ot my server_addr of type sockaddr_in
    bcopy((char *)server -> h_addr,
        (char *)&server_addr.sin_addr.s_addr,
        server->h_length);
        // Enndianness
    server_addr.sin_port = htons(80);
    // connecting by casting it to more genneric structure sockaddr, via my socket
    if(connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) <0) {
        printf("connection failed ! \n");
        return 1;
    }
    printf("Successfully connected to Google!\n");

    char *message = "GET /search?q=c+programming HTTP/1.1\r\nHost: google.com\r\nConnection: close\r\n\r\n";
    write(socket_fd, message, strlen(message));


    char buffer[4096];
    bzero(buffer, sizeof(buffer));
    int n;
    // if n is greater than 0 than yes we scooped more data
    while((n = read(socket_fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';   // the nth position is  however many bytes google returned, so this line tacks null terminator at end
        printf("%s", buffer);
        bzero(buffer, sizeof(buffer));
    }

    char serv_resp[256];
    recv(socket_fd, &serv_resp, sizeof(serv_resp), 0);
    printf("--- Server Response ---\n%s\n", serv_resp);

    close(socket_fd);
    return 0;
}