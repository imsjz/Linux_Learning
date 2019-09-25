/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-25 16:25:32
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(){

    char buf[2] = "h2";
    printf("buf = %s", buf);

    char *buf2 = "hello";
    printf("strlen of buf2 = %d\n", strlen(buf2));
    

    return 0;
}