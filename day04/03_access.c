/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-08-30 13:36:27
 */
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    if(argc != 2){
        perror("./a.out filename");
        return -1;
    }
    if(access(argv[1], R_OK) == 0){
        printf("%s read ok!\n", argv[1]);
    }
    if(access(argv[1], W_OK) == 0) printf("%s write ok!\n", argv[1]);
    if(access(argv[1], X_OK) == 0) printf("%s exec ok!\n", argv[1]);
    if(access(argv[1], F_OK) == 0) printf("%s exists!\n", argv[1]);
    

    return 0;
}