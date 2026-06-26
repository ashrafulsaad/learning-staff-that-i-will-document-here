#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[100];
    int num1, num2;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    sprintf(buffer, "%d %d", num1, num2);

    sendto(sockfd, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr *)&server_addr,
           sizeof(server_addr));

    printf("Numbers sent to server.\n");

    close(sockfd);

    return 0;
}