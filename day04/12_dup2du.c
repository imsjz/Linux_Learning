/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-01 18:37:36
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    //先备份现场
    int outfd = dup(STDOUT_FILENO);
    //先做重定向
    int fd = open("world", O_WRONLY | O_CREAT, 0666);
    dup2(fd, STDOUT_FILENO);
    //打印到文件
    printf("hello world\n");
    //文件是全缓冲，所以要刷新一波
    fflush(stdout);
    //需要恢复1 重新对应 标准输出
    dup2(outfd, STDOUT_FILENO);

    printf("hello world\n");
    close(fd);
    return 0;
}