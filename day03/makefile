
#get all .c files
SrcFiles=$(wildcard *.c)
#all .c files --> .o files
ObjFiles=$(patsubst %.c, %.o, $(SrcFiles))

all:app

#目标文件用法 $(var)
app:$(ObjFiles)
	gcc -o $@ -I ./include $(ObjFiles)

#模式匹配规则，$@,$<, 这样的变量，只能在规则中出现
%.o:%.c
	gcc -c $< -I ./include -o $@



test:
	echo $(SrcFiles)
	echo $(ObjFiles1)

#定义伪目标，防止有歧义
.PHONY:clean  all

clean:
	-@rm -f *.o
	@rm -f app
