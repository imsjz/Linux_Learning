#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "head.h"

typedef struct TTfunInfo{
    int fun_type; //函数类型
    int a;//first element
    int b; //second element
    char funname[10]; //function name
}TfunInfo;

int main(int argc, char *argv[])
{
    int a = 2;
    int i = 0;
    int a1= 10, b1 = 5;
    TfunInfo funinfo[2];
    char *msg = "I will die!";
    msg[0] = '1';
    if(argc == 3){
        a1 = atoi(argv[1]);
        b1 = atoi(argv[2]);
        funinfo[0].a = a1;
        funinfo[0].b = b1;
        funinfo[1].a = a1;
        funinfo[1].b = b1;
    }
    for(i = 0; i < 2; ++i){
        printf("i==%d, LINE=%d\n", i, __LINE__);
        if(i == 0){
            funinfo[0].fun_type = 1; //call sum
            printf("begin call sum\n");
            strcpy(funinfo[0].funname, "sum");
            sum(funinfo[0].a, funinfo[0].b);
        }
        if(i == 1){
            funinfo[1].fun_type = 2;
            printf("begin call mul\n");
            strcpy(funinfo[1].funname, "mul");
            mul(funinfo[1].a, funinfo[1].b);
        }
    }
    printf("byebye\n");
    return 0;
}

