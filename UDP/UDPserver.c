// UDP protocol server
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../generatePassword/generatePassword.h" //生成密码 传入字符串地址 返回缓冲区地址

int main(void)
{
    // 创建套接字
    printf("创建套接字...\n");
    int socketfd = socket(PF_INET, SOCK_DGRAM, 0); // fd == file descriptor 通信套接字
    if (socketfd == -1)
    {
        perror("socket");
        return -1;
    }
    printf("创建套接字%d成功\n", socketfd);

    // 准备地址结构 服务器确认用哪一个端口发送数据
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(9800);

    // 绑定套接字
    if (bind(socketfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind");
        return -1;
    }
    printf("绑定地址成功...\n");

    for (;;)
    {
        // 接收准备
        char buffer[128] = {};
        struct sockaddr client;
        socklen_t length = sizeof(client);
        // 接收数据
        ssize_t size = recvfrom(socketfd,                   // 通信套接字fd
                                buffer,                     // 缓冲区首地址
                                sizeof(buffer) - 1,         // 缓冲区大小 ssize_t == long
                                0,                          // flag
                                (struct sockaddr *)&client, // 客户端对象
                                &length);                   // 地址长度
        printf("成功接收到数据:%s", buffer);
        // 返回接收到的数据大小

        if (size == -1)
        {
            perror("recvfrom");
            return -1;
        }

        if (strcmp(buffer, "shutdown") == 0)
        {
            printf("关机\n");
            strcpy(buffer, "服务器关闭成功!");
            if(sendto(socketfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client, sizeof(client)) == -1)
            {
                perror("sendto");
                return -1;
            }
            break;
        }
        
        // 数据处理
        generatePassword(buffer);
        printf("生成密码成功，准备发送数据:%s\n", buffer);
        if (sendto(socketfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client, sizeof(client)) == -1)
        {
            perror("sendto");
            return -1;
        }
        printf("发送数据成功!\n");
    }

    // 关闭套接字
    close(socketfd);
    printf("服务器套接字关闭");
    return 0;
}