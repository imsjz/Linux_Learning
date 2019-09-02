/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-29 13:02:20
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("./a.out filename\n");
        return -1;
    }
    //1.open
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
    //2.lseek,拓展文件
    int ret = lseek(fd, 1024, SEEK_END);
    //需要至少写一次，否则不能保存
    write(fd, "a", 1);

    //3. 关闭文件描述符
    close(fd);
    return 0;
}