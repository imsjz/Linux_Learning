//-rwxrwxr-x 2 sanjay sanjay 18 8月  30 13:47 hello
/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 13:36:27
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


int main(int argc, char *argv[]){

    if(argc != 2){
        perror("./a.out filename");
        return -1;
    }
    //调用stat 得到文件信息
    struct stat sb;
    //stat(argv[1], &sb); //stat带有穿透功能，比如查看软链接信息会直达原文件的信息
    lstat(argv[1], &sb); //lstat不带穿透功能
    //解析属性信息， st_mode, uid, gid, time
    //st_mode
    char stmode[11] = {0};
    memset(stmode, '-', sizeof(stmode) - 1);
    if(S_ISREG(sb.st_mode))
        stmode[0] = '-';// 普通文件
    else if(S_ISDIR(sb.st_mode))
        stmode[0] = 'd';
    else if(S_ISCHR(sb.st_mode))
        stmode[0] = 'c';
    else if(S_ISBLK(sb.st_mode))
        stmode[0] = 'b';
    else if(S_ISFIFO(sb.st_mode))
        stmode[0] = 'p';
    else if(S_ISLNK(sb.st_mode))
        stmode[0] = 'l';
    else if(S_ISSOCK(sb.st_mode))
        stmode[0] = 's';
    
    //解析权限
    if(sb.st_mode & S_IRUSR) stmode[1] = 'r';
    if(sb.st_mode & S_IWUSR) stmode[2] = 'w';
    if(sb.st_mode & S_IXUSR) stmode[3] = 'x';

    if(sb.st_mode & S_IRGRP) stmode[4] = 'r';
    if(sb.st_mode & S_IWGRP) stmode[5] = 'w';
    if(sb.st_mode & S_IXGRP) stmode[6] = 'x';

    if(sb.st_mode & S_IROTH) stmode[7] = 'r';
    if(sb.st_mode & S_IWOTH) stmode[8] = 'w';
    if(sb.st_mode & S_IXOTH) stmode[9] = 'x';

    //-rwxrwxr-x 2 sanjay sanjay 18 8月  30 13:47 hello
    //分析 用户名，组名可以通过函数getpwuid  getgrgid获取
    //时间获取
    struct tm *filetm = localtime(&sb.st_atime);
    char timebuf[20] = {0};
    sprintf(timebuf, "%d月  %d %02d:%02d", filetm->tm_mon+1, filetm->tm_mday, filetm->tm_hour, filetm->tm_min);

    printf("%s %lu %s %s %ld %s %s\n", stmode, sb.st_nlink, getpwuid(sb.st_uid)->pw_name, getgrgid(sb.st_gid)->gr_name, \
           sb.st_size, timebuf , argv[1]);

    return 0;
}