#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT            9990
#define SERVER_ADDR     "127.0.0.1"
#define MAXBUF          1024

int main() {
    // see server for more information on
    // functions/structs used here
    int sockfd;
    struct sockaddr_in dest;
    char buffer[MAXBUF];
    char sbuf[MAXBUF];

    // create a typical TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        exit(errno);
    }

    // init address struct for use
    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT);

    // convert the address and place it in the dest struct
    if (inet_aton(SERVER_ADDR, (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
        perror(SERVER_ADDR);
        exit(errno);
    }

    // connect to the server
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
        perror("Connect ");
        exit(errno);
    }

    // clear the buffer and get message from user
    bzero(buffer, MAXBUF);
    printf("message to send-> ");
    fgets(buffer, MAXBUF, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    // send the message and receive reply from server
    send(sockfd, buffer, MAXBUF, 0);
    recv(sockfd, sbuf, MAXBUF, 0);
    printf("recv from server-> %s\n", sbuf);

    // clean up and exit
    close(sockfd);
    return (0);
}