/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-15 15:05:50
 */
#include <stdio.h>
#include <string.h>

int main(){

    char str1[] = "hello";
    char str2[] = {'h','e','l','l','o', '\0'};
    char str3[] = {'h', 'e','l','l', 'o'};


    printf("str1:%s\n", str1);
    printf("str2:%s\n", str2);
    printf("str3:%s\n", str3);
    
    printf("strlen of str1 = %ld\n", strlen(str1));
    printf("strlen of str1 = %ld\n", strlen(str2));
    printf("strlen of str1 = %ld\n", strlen(str3));

    return 0;
}