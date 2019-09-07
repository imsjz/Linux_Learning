/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-05 14:51:10
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){


    char buf[5];

    fgets(buf, 5, stdin);

    printf("strlen(buf) = %d\n", strlen(buf));
    printf(buf);

    return 0;
}