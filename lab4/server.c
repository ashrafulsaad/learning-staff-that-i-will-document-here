#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd,
         (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    listen(server_fd, 5);

    printf("Server started on port %d\n", PORT);

    while(1)
    {
        client_fd = accept(server_fd,
                          (struct sockaddr *)&client_addr,
                          &addr_len);

        printf("New Client Connected\n");

        pid_t pid = fork();

        if(pid == 0)
        {
            close(server_fd);

            while(1)
            {
                memset(buffer,0,sizeof(buffer));

                int n = read(client_fd,
                            buffer,
                            sizeof(buffer));

                if(n <= 0)
                    break;

                printf("Client: %s\n", buffer);

                if(strcmp(buffer,"logout\n")==0 ||
                   strcmp(buffer,"logout")==0)
                {
                    printf("Client Logged Out\n");
                    break;
                }

                write(client_fd,
                      buffer,
                      strlen(buffer));
            }

            close(client_fd);
            exit(0);
        }
        else
        {
            close(client_fd);
        }
    }

    return 0;
}