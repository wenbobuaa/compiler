#include <stdio.h>
#include <stdlib.h>
#include "const.h"

#define norw	21	//保留字个数
#define txmax	100	//符号表的长度
#define nmax	14	//数字的最大长度
#define al	18	//标识符的最大长度
#define lmax	81  //行缓冲区的最大长度
#define strmax	100	//字符串最大长度
#define lsym 44	//symbol的个数

SYMBOL symbol;//当前读取的单词的类型
char ch;//正在处理的字符
char token[al];//保存当前的一个标识符
int num;//整数
char cha;//字符
char str[strmax];//字符串
char line[81];//行缓冲区
int ll = 1;//行号
int cc = 0;//行缓冲区指针
int kk = 0;//标识符栈指针
int kkk = 0;//字符串栈指针
char * reserverTable[norw];//保留字表
FILE * In;
FILE * Out;
FILE * MOUT;
int errornum;

void getChar();//读一个字符
int getLine();//读新的一行
void clearToken();//当前字符串读取完毕
void clearString();//字符串输入结束
int isEnd();
int isSpace();//空格
int isNewline();//换行
int isTab();//tab
int isLetter();//字母
int isChar();//字符
int isDigit();//数字
int isColon();//冒号
int isComma();//逗号
int isSemi();//分号
int isPeri();//句号
int isSquot();//单引号
int isDquot();//双引号
int isLbrac();//左中括号
int isRbrac();//右中括号
int isEqu();//等号
int isLess();//小于号
int isGreat();//大于号
int isPlus();//+
int isMinus();//-
int isStar();//*
int isDivi();///
int isLpar();//(
int isRpar();//)
void catToken();//添加一个字符
void catString();//给字符串添加一个字符
void retract();//回退一个字符
SYMBOL reserver();//查保留字
int transNum();//转化成整数
void erro(int sw);//报错
void initReserver();//初始化保留字表
void getsym();//词法分析程序

int symNeed[lsym];//符合要求的类型表
void grammar();//语法分析程序
void procedure();//程序
void subPro();//分程序

_TAB tab[txmax];//符号表
_ATAB atab[40];//数组信息向量表
_BTAB btab[40];//分程序表
int display [40];//分程序索引表
int tabtop;//符号表栈顶指针
int atabtop;//数组信息向量表栈顶指针
int btabtop;//分程序表栈顶指针
int termnum;//未处理的表项
_TAB tabnow;//当前一个符号表项
_ATAB atabnow;//当前一个数组表项
_BTAB btabnow;//当前一个分程序表项
//int publev = 0;//当前层数
//int adrtop;//当前地址
//extern int opttop;//当前指令位置
_CODE ctab[1000];//四元式表
int ctabtop;//当前指令位置
_CODE ctabnow;//当前指令内容
int Tnum = 0;//中间变量序号
int Label = 0;//标志序号

int regtab[32];
int regtabbuf[32];
int regnum[32];
_VARTAG vartab[100];
int vartabtop;
int nowctabadr;
int ref;

void subPro(int lev, int levtop, int adr);//分程序
void consDef(int lev, int levtop);//常量定义
void constAnaly(int lev, int levtop);//常量分析
void varDef(int lev, int levtop, int adr);//变量定义
void proHead(int lev, int levtop);//过程头部
void funcHead(int lev, int levtop);//函数头部
void formParaList(int lev, int levtop);//形式参数表
void Type(int lev, int levtop, int * adr);//类型
_SYMBOL baseType(int lev, int levtop);//基本类型
void formParaSeg(int lev, int levtop, int * adr);//形式参数段
void comState(int btablev, int lev, int levtop, int adr);//复合语句
void state(int btablev, int lev, int levtop, int adr);//语句
void assignment(int btablev, int i, int lev, int levtop, int adr);//赋值语句
void conditionState(int btablev, int lev, int levtop, int adr);//条件语句
void caseState(int btablev, int lev, int levtop, int adr);//情况语句
void proCall(int btablev, int i, int lev, int levtop, int adr);//过程调用
void readState(int btablev, int lev, int levtop, int adr);//读语句
void writeState(int btablev, int lev, int levtop, int adr);//写语句
void loop(int btablev, int lev, int levtop, int adr);//循环
int expression(int btablev, int lev, int levtop, int adr);//表达式
void condition(int btablev, int lev, int levtop, int adr);//条件
void caseelement(int btablev, int i, int lev, int levtop, int adr);//情况元素表
void actParaList(int btablev, int i, int lev, int levtop, int adr);//实际参数表
int term(int btablev, int lev, int levtop, int adr);//项
int factor(int btablev, int lev, int levtop, int adr);//因子
int funcCall(int btablev, int lev, int levtop, int adr);//函数调用

int tabtest(int lev, char * name);//查重符号表
void tabtype(_SYMBOL symbol, int ternnum);//批量填充类型
void tabadr(int * adr, int num, int termnum);
void tabref(int atabtop, int termnum);
void tablink(int levtop, int termnum);
int tabfind(char * name, int levtop);//查符号表
void gen(int lev, int btablev, char * des, _OP opt, char * fir, char * sec);//生成四元式
void list_();//列出当前四元式
void constant(int lev, int btablev);//常量
void trans();//翻译
