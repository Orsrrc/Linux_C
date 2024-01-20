//UDP protocol server 
#include <stdio.h>
#include<sys/socket.h>
int main(void)
{
    //创建套接字
    printf("创建套接字");
    int SocketID = socket(PF_INET, SOCK_DGRAM, 0 );
    if(SocketID == -1)
    {
        perror("socket");
        return -1;
    }

    //准备地质结构


    return 0;
}