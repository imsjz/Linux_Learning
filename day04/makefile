#####  xxxx.c --->  xxx

SrcFiles=$(wildcard *.c)
TargetFiles=$(patsubst %.c, %, $(SrcFiles))

all:$(TargetFiles)

%:%.c
	gcc -o $@ $^ -g

clean:
	rm -f $(TargetFiles)
