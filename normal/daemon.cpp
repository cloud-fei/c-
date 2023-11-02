#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/file.h>

void signalHandle(int signum){

}

int main(){
    //创建子进程
    pid_t pid = fork()；

    if(pid < 0){
        std:cerr << "Failed to create daemon process!" << std::endl;
    }else if(pid > 0){
        //父进程退出
        return 0;
    }

    //子进程继续执行 
    
    //脱离控制终端，返回新的会话id
    setsid();

    //关闭文件描述符
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //修改工作目录
    chdir("/");

    //重定义文件描述符
    open("/dev/null",O_RDONLY);
    open("/dev/null",O_RDWR);
    open("/dev/null",O_RDWR);

    //注册信号处理函数
    signal(SIGTERM, signalHandle)

    //守护进程业务逻辑
    while(true){
        //业务代码

        sleep(1);
    }

    return 0;

}