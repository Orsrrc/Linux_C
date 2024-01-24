//UDP protocol server 
#include <stdio.h>
#include<sys/socket.h>
int main(void)
{
    //创建套接字
    printf("创建套接字\n");
    int socketfd = socket(PF_INET, SOCK_DGRAM, 0 ); //fd == file descriptor
    if(socketfd == -1) 
    {
        perror("socket");
        return -1;
    }

    //准备地址结构
    struct sockaddr server;
    server.sa_family = AF_INET;

    //绑定套接字
    if(bind(socketfd, &server, (socklen_t)server.sa_len) == -1)
    {
        perror("bind");
        return -1;
    }
    return 0;
}