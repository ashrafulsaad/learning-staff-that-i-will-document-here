#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);
    char buffer[100];
    int num1, num2, sum;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Server waiting...\n");

    // Receive data
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client_addr, &len);

    sscanf(buffer, "%d %d", &num1, &num2);

    sum = num1 + num2;

    printf("Received Numbers: %d %d\n", num1, num2);
    printf("Sum = %d\n", sum);

    close(sockfd);

    return 0;
}