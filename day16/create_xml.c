/*
 * @Author: sanjayzhong
 * @Github: https://github.com/sanjayzzzhong
 * @Date: 2019-09-25 11:23:47
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <mxml.h>

int main(int argc, char *argv[]){

    //文件头
    mxml_node_t* root = mxmlNewXML("1.0");

    //根标签 -- china
    mxml_node_t* china = mxmlNewElement(root, "china");
    //子标签
    mxml_node_t *city = mxmlNewElement(china, "city");
    mxml_node_t *info = mxmlNewElement(city, "name");
    //标签赋值
    mxmlNewText(info, 0, "北京");
    //设置属性
    mxmlElementSetAttr(info, "isbig", "yes");
    //面积
    info = mxmlNewElement(city, "area");
    mxmlNewText(info, 0, "16410 平方公里");

    //继续china的子标签
    city = mxmlNewElement(china, "city");
    info = mxmlNewElement(city, "name");
    //标签赋值
    mxmlNewText(info, 0, "东京");

    //数据保存到磁盘文件
    FILE *fp = fopen("china_via_code.xml", "w");

    mxmlSaveFile(root, fp, MXML_NO_CALLBACK);

    //释放资源
    free(fp);
    mxmlDelete(root);

    return 0;
}