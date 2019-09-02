/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 16:13:32
 */
#include <stdio.h>
#include <link.h>
#include <unistd.h>


int main(){

    char buf[32] = {0};
    int ret = readlink("hello.soft1", buf, sizeof(buf));
    if(ret){
        printf("buf is %s\n", buf);
    }
    unlink("hello");
    return 0;
}