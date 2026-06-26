#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    char buf[100];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(60018);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    // Bind socket to address
    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Server is running, waiting for messages...\n");

    addr_size = sizeof(clientAddr);

    // Receive message from client
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&clientAddr, &addr_size);
    printf("Received from client: %s\n", buf);

    // Send reply to client
    strcpy(buf, "Hello from Server!");
    sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr*)&clientAddr, addr_size);

    close(sockfd);
    return 0;
}
