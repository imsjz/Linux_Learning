/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-04 13:49:18
 */
#include <stdio.h>
#include <unistd.h>

int main(){

    short int a = 0x0123;
    char b = *(char *)&a; //先取a的地址，然后将其强制转换为char类型(8个字节),然后再取内容，如果b里面是01,那么是大端，如果是23，则为小端
    if(b == 0x01){
        printf("大端\n");
    }
    else if(b == 0x23){
        printf("小端\n");
    }
    printf("bytes of short: %ld\n", sizeof(short));

    return 0;
}