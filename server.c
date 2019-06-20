/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** server.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4242

int main() {

    int sockfd;
    int ret;
    struct sockaddr_in serverAddr;
    int newSocket;
    struct sockaddr_in newAddr;
    socklen_t addr_size;

    char buffer[1024];
    char *buff_s;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("[-]Error in connection.\n");
        exit(1);
    }
	printf("[+]Server Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        printf("[-]Error in binding.\n");
        exit(1);
    }
    printf("[+]Bind to port %d\n", PORT);

    if (listen(sockfd, 10) == 0) {
        printf("[+]Listening....\n");
    } else {
        printf("[-]Error in binding.\n");
    }
    while (1) {
        newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
        if(newSocket < 0) {
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
        close(sockfd);
        buff_s = strdup("WELCOME\n");
        while (1) {
                sendto(newSocket, buff_s, sizeof(buff_s), 0, (struct sockaddr*)&newAddr, &addr_size);
                recv(newSocket, buffer, 1024, 0);
                if (strcmp(buffer, ":exit") == 0){
                    printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break;
                } else {
                    printf("Client: %s\n", buffer);
                    send(newSocket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }
    close(newSocket);
	return 0;
}
