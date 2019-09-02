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
    int fd = open(argv[1], O_RDWR | O_CREAT, 0664);
    //2.lseek,得到返回值
    int ret = lseek(fd, 0, SEEK_END);
    printf("file size is %d\n", ret);

    //3. 关闭文件描述符
    close(fd);
    return 0;
}