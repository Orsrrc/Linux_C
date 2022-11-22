#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
void write_time(int num)
{
    time_t rawtime;
    struct tm * timeinfo;
    //获取时间
    time(&rawtime);
#if 0
    //转为本地时间
    timeinfo = localtime(&rawtime);
    //转为标准ASCLL时间格式
    char * cur = asctime(timeinfo);
#else
    char * cur = ctime(&rawtime);
#endif

    //将得到的时间写入文件
    int fd = open("/home/Item/timelog.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    if(-1 == fd)
    {
        perror("open");
        exit(1);
    }
    //写文件
    int ret = write(fd, cur, strlen(cur) + 1);
    if (ret == -1)
    {
        perror("write");
        exit(1);
    }
    //关闭文件
    close(fd);
}

int main(int argc, const char * argv[])
{
	//创建子进程 父进程退出
	pid_t pid = fork();
	if( pid < 0)
	{
		perror("fork");
		return 1;
	}
	if(0 == pid)
	{   //子进程
		//创建新的会话
		setsid();
		//更改进程的执行目录
		chdir("/home/Item");
		//更改掩码(0022)
		umask(0022);
		
		//关闭文件描述符
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	
		//注册信号捕捉函数
		//先注册 再定时
		struct sigaction sigact;
		sigact.sa_flags = 0;
		sigemptyset(&sigact.sa_mask);
		sigact.sa_handler = write_time;
		sigaction(SIGALRM, &sigact, NULL);
		
		//设置定时器
		struct itimerval act;
		//定时周期
		act.it_interval.tv_sec = 2;
		act.it_interval.tv_usec = 0;
		//设置第一次触发定时器时间
		act.it_value.tv_sec = 2;
		act.it_value.tv_usec = 0;
		//开始计时
		setitimer(ITIMER_REAL, %act, NULL);
        while(1);
		}
	else{ //父进程 
		exit(1);	
		}	
    return 0;
}
