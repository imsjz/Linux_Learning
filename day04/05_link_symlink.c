/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 16:13:32
 */
#include <stdio.h>
#include <link.h>
#include <unistd.h>


int main(){

    //link("hello", "hello.hard1");
    symlink("hello", "hello.soft1");
    return 0;
}