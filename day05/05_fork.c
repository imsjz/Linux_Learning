#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

int main(){
    printf("begin..."); //标准输出是行缓冲
    fork();
    printf("end...\n");
    return 0;
}