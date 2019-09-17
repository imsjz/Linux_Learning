/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-17 14:37:55
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    //主要测试一下打开文件非阻塞的情况,会返回什么
    //权限不够...测试失败...
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags);
    char buf[64] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));

    printf("ret = %d\n", ret);

    return 0;
}