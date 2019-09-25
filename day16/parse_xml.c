/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-25 12:55:57
 */
#include <stdio.h>
#include <mxml.h>

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("./a.out filename\n");
        return 0;
    }
    //加载xml文件
    FILE *fp = fopen(argv[1], "r");
    mxml_node_t *root = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);

    //找到第一个object节点
    mxml_node_t *object = mxmlFindElement(root, root, "object", NULL, NULL, MXML_DESCEND);
    //循环查找
    while(object){

        // //向下移动一个节点
        // mxml_node_t *name = mxmlWalkNext(object, root, MXML_DESCEND);   //用walknext遇到换行解析有问题
        mxml_node_t *name = mxmlFindElement(object, root, "name", NULL, NULL, MXML_DESCEND);
        printf("object name: %s\n", mxmlGetText(name, NULL));

        object = mxmlFindElement(object, root, "object", NULL, NULL, MXML_NO_DESCEND);
    }

    mxmlDelete(root);
    free(fp);

    return 0;
}