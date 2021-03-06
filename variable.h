#include <stdio.h>
#include "const.h"
//#define DEBUG

extern _SYMBOL symbol;//当前读取的单词的类型
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
extern FILE * MOUT;
extern int errornum;

extern int symNeed[lsym];//符合要求的类型表

extern _TAB tab[txmax];//符号表
extern _ATAB atab[40];//数组信息向量表
extern _BTAB btab[40];//分程序表
extern int display [40];//分程序索引表
extern int tabtop;//符号表栈顶指针
extern int atabtop;//数组信息向量表栈顶指针
extern int btabtop;//分程序表栈顶指针
extern int termnum;//未处理的表项
extern _TAB tabnow;//当前一个符号表项
extern _ATAB atabnow;//当前一个数组表项
extern _BTAB btabnow;//当前一个分程序表项
//extern int publev;//当前层数
//extern int adrtop;//当前地址
//extern int opttop;//当前指令位置
extern _CODE ctab[10000];//四元式表
extern int ctabtop;//当前指令位置
extern _CODE ctabnow;//当前指令内容
extern int Tnum;//中间变量序号
extern int Label;//标志序号

extern int regtab[32];//保存寄存器的使用信息
extern int regtabbuf[32];//regtab的备份
extern int regnum[32];//reg的使用次数
extern _VARTAG vartab[100];
extern int vartabtop;
extern int nowctabadr;
extern int ref;
