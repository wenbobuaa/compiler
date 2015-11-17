#include <stdio.h>
#include "const.h"

extern SYMBOL symbol;//当前读取的单词的类型
extern char ch;//正在处理的字符
extern char token[al];//保存当前的一个标识符
extern int num;//整数
extern char cha;//字符
extern char str[strmax];//字符串
extern char line[81];//行缓冲区
extern int ll;//行号
extern int cc;//行缓冲区指针
extern int kk;//标识符栈指针
extern int kkk;//字符串栈指针
extern char * reserverTable[norw];//保留字表
extern FILE * In;
extern FILE * Out;
