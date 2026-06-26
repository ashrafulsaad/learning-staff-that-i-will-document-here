#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    char buf[100];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(60018);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    addr_size = sizeof(serverAddr);

    // Send message to server
    strcpy(buf, "Hello from Client!");
    sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr*)&serverAddr, addr_size);

    // Receive reply from server
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&serverAddr, &addr_size);
    printf("Received from server: %s\n", buf);

    close(sockfd);
    return 0;
}
