/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 21:01:30
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

    //先切换工作目录
    chdir("bbb");
    int fd = open("temp", O_WRONLY | O_CREAT, 0664);
    //留下点痕迹
    write(fd, "hello", 5);
    close(fd);
    //显示当前工作目录
    char buf[256];
    getcwd(buf, sizeof(buf));
    printf("buf is [%s]\n", buf);
    return 0;
}