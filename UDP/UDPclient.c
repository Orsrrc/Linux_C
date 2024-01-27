#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
    // 创建套接字
    int socketfd = socket(PF_INET, SOCK_DGRAM, 0);

    if (socketfd == -1)
    {
        perror("socket");
        return -1;
    }
    printf("创建套接字%d成功!\n", socketfd);
    // 准备地址结构
    struct sockaddr_in client; // struct  in_addr sin_addr;
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(9800);

    while (1)
    {
        // 准备数据
        char buffer[128] = {};
        scanf("%s", &buffer);
        printf("准备发送数据:%s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
        {
            break;
        }
        sendto(socketfd, buffer, strlen(buffer), 0, (struct sockaddr*)&client, sizeof(client));
        printf("已发送数据，等待服务器返回数据...\n");
        socklen_t length = sizeof(client);
        ssize_t size = recvfrom(socketfd, buffer, sizeof(buffer) - 1, 0, &client, &length);
        if(size == -1)
        {
            perror("recvfrom");
            return -1;
        }

        if(strcmp(buffer, "服务器关闭成功!\n") == 0)
        {
            printf("%s", buffer);
            break;
        }
        printf("收到消息:%s\n", buffer);
    }
    close(socketfd);
    printf("套接字关闭，程序结束...\n");
}