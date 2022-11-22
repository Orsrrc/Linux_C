#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#define SIZE 48

void write_time(char * file_name)
{
    int fd = -1;
    fd = open("/home/orsrrc/Item/Progress/timelog.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }
    int ret = -1;
    ret = write(fd, file_name, strlen(file_name) + 1);
    if(ret == -1)
    {
        perror("write");
        exit(1);
    }
    close(fd);
}


int main(){
    //1、创建子进程 父进程退出
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return 0;
    }
    if(0 == pid)
    {//子进程
       //2、创建新的会话
       pid_t sid =  setsid();
       if(sid < 0)
       {
           perror("setsid");
           return 0;
       }
       //3、更改当前工作目录
      int ret =  chdir("/");
       if(-1 == ret)
       {
           perror("chdir");
           return 0;
       }
       //4、设置权限掩码 umask函数总是成功
       umask(0022);
#if 0
       //5、关闭文件描述符
       close(STDIN_FILENO);
       close(STDOUT_FILENO);
       close(STDERR_FILENO);
#endif
       //防止子进程退出
       while(1){
           //6、执行核心任务 每隔一秒输出当前时间到/tmp/txt.log文件中
           //获取当前时间 以秒为单位 从1970-01-01 00：00：00开始到现在的秒数
           time_t t = time(NULL); //函数的参数可以为空
           if(-1 == t)
           {
               perror("time");
               return 0;
           }
           struct tm *pT = NULL;
           pT = localtime(&t);
           if (NULL == pT)
           {
               printf("getLocaltime filed...\n");
           }
            //转换为文件名 将数组转换为字符串
            char file_name[SIZE];
            memset(file_name, 0 , SIZE);
            sprintf(file_name, "%d%d%d%d%d%d.log", pT->tm_year + 1990, pT->tm_mon + 1, pT->tm_mday, pT->tm_hour, pT->tm_min, pT->tm_sec);
          //终端中输出文件名
            printf("file name :%s\n", file_name);
          // system(file_name);
        write_time(file_name);
           sleep(1);

       }
    }
    else{
        //父进程退出
        exit(1);
    }
}
