#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
    close(0); //close stdout
    int fd = open("1.log", O_CREAT | O_TRUNC | O_RDONLY, 0664);
    printf("fd = %d\n", fd);

    printf("hello world\n");//由于这里关了1，并且把1绑定到了1.log中
    fflush(stdout);
    close(fd);
    return 0;
}

