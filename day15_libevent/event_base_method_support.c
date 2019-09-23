/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-20 16:51:46
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <event2/event.h>

int main(int argc, char *argv[]){


    //创建一个事件处理框架event_base
    struct event_base *base = NULL;
    base = event_base_new();
    //打印支持后端 -- io转接函数
    const char **meths = event_get_supported_methods();
    for(int i = 0; meths[i] != NULL; ++i){
        printf("%s\n", meths[i]);
    }

    //当前使用的io转接函数
    printf("current = %s\n", event_base_get_method(base));

    pid_t pid = fork();
    if(pid == 0){
        //在子进程中重新初始化
        event_reinit(base);
    }

    //添加事件...

    //事件循环:启动base的事件循环
    event_base_dispatch(base);

    //释放event_base
    event_base_free(base);
    return 0;
}