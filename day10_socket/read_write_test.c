/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-05 13:33:28
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 4096 

int main(){

    char buf[BUFSIZE];

    int read_size = read(STDIN_FILENO, buf, sizeof(buf)); //这里用sizeof(buf) 来指定最大可以读取多少数据
    //read_size 返回的是读取到多少数据
    printf("read_size = %d\n", read_size);
    int write_size = write(STDOUT_FILENO, buf, read_size);
    //如果将read_size换成sizeof(buf)
    //int write_size = write(STDOUT_FILENO, buf, sizeof(buf));
    //write_size 返回的是写入多少数据
    printf("write_size = %d\n", write_size);

    return 0;
}