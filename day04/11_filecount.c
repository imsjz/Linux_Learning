/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 21:15:22
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int count = 0; //定义一个全局的计数

int DirCount(char *dirname){

    printf("%s\n", dirname);
    //打开目录
    DIR *dirp = opendir(dirname);
    if(dirp == NULL){
        perror("opendir err");
        return -1;
    }
    //循环读目录，如果是普通文件，则count++,如果是目录，继续调用DirCount
    struct dirent *dentp = NULL;
    while((dentp = readdir(dirp)) != NULL){//如果为NULL，代表读到目录末尾
        printf("dirname: %s, dtype:%d\n", dentp->d_name, dentp->d_type);
        if(dentp->d_type == DT_DIR){
            //如果是目录
            //char newdirname[256] = {0};
            if(strcmp(".", dentp->d_name) == 0 || strcmp("..", dentp->d_name) == 0){
                continue;
            }
            else{
                //注意进程的工作路径，不能直接打开子目录
                //使用dirname拼接下一级子目录
                char newdirname[1024] = {0};
                sprintf(newdirname,"%s/%s", dirname, dentp->d_name);
                DirCount(newdirname);
            }
        }
        else if(dentp->d_type == DT_REG){
            count++;
            printf("dname:%s\n", dentp->d_name);
        }
    }
    closedir(dirp);
    return 0;
}

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("./a.out dirname\n");
        return -1;
    }
    DirCount(argv[1]);
    printf("count = %d\n", count);


    return 0;
}