#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(){
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid == 0){
        //son
        //son --> ps
        //关闭读端
        cloese(fd[0]);
        //1.重定向
        dup2(fd[1], STDOUT_FILENO);
        //2.execlp
        execlp("ps", "ps", "aux", NULL);
    } else if(pid > 0){
        //parent
        //parent --> grep bash
        //关闭写端
        close(fd[1]);
        //1.重定向
        dup2(fd[0], STDIN_FILENO);
        //2.execlp
        execlp("grep", "grep", "bash", NULL);
    }

    return 0;
}