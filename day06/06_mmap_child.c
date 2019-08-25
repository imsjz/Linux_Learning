#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    //先创建映射区
    int fd = open("mem.txt", O_RDWR);
    int *mem = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(mem == MAP_FAILED){
        perror("mmap error");
        return -1;
    }
    //fork子进程
    pid_t pid = fork();
    //父子进程交替修改数据
    if(pid == 0){
        //son
        *mem = 100;
        printf("child *mem=%d\n", *mem);
        sleep(3);
        printf("child *mem=%d\n", *mem);
    }
    else if(pid > 0){
        //parent
        sleep(1);
        printf("parent *mem=%d\n", *mem);
        *mem = 1001;
        printf("parent *mem=%d\n", *mem);
        wait(NULL);
    }

    munmap(mem, 4);
    close(fd);
    return 0;
}