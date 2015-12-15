#include <stdlib.h>
#include "const.h"

extern void getChar();//读一个字符
extern int getLine();//读新的一行
extern void clearToken();//当前字符串读取完毕
extern void clearString();//字符串输入结束
extern int isEnd();
extern int isSpace();//空格
extern int isNewline();//换行
extern int isTab();//tab
extern int isLetter();//字母
extern int isChar();//字符
extern int isDigit();//数字
extern int isColon();//冒号
extern int isComma();//逗号
extern int isSemi();//分号
extern int isPeri();//句号
extern int isSquot();//单引号
extern int isDquot();//双引号
extern int isLbrac();//左中括号
extern int isRbrac();//右中括号
extern int isEqu();//等号
extern int isLess();//小于号
extern int isGreat();//大于号
extern int isPlus();//+
extern int isMinus();//-
extern int isStar();//*
extern int isDivi();///
extern int isLpar();//(
extern int isRpar();//)
extern void catToken();//添加一个字符
extern void catString();//给字符串添加一个字符
extern void retract();//回退一个字符
extern SYMBOL reserver();//查保留字
extern int transNum();//转化成整数
extern void erro(int sw);//报错
extern void initReserver();//初始化保留字表
extern void getsym();//词法分析程序

extern void grammar();//语法分析程序
extern void procedure();//程序
extern void subPro(int lev, int levtop, int adr);//分程序
extern void consDef(int lev, int levtop);//常量定义
extern void constAnaly(int lev, int levtop);//常量分析
extern void varDef(int lev, int levtop, int * adr);//变量定义
extern void proHead(int lev, int levtop);//过程头部
extern void funcHead(int lev, int levtop);//函数头部
extern void formParaList(int lev, int levtop);//形式参数表
extern void Type(int lev, int levtop, int * adr);//类型
extern _SYMBOL baseType(int lev, int levtop);//基本类型
extern void formParaSeg(int lev, int levtop, int * adr);//形式参数段
extern void comState(int btablev, int lev, int levtop, int adr);//复合语句
extern void state(int btablev, int lev, int levtop, int adr);//语句
extern void assignment(int btablev, int i, int lev, int levtop, int adr);//赋值语句
extern void conditionState(int btablev, int lev, int levtop, int adr);//条件语句
extern void caseState(int btablev, int lev, int levtop, int adr);//情况语句
extern void proCall(int btablev, int i, int lev, int levtop, int adr);//过程调用
extern void readState(int btablev, int lev, int levtop, int adr);//读语句
extern void writeState(int btablev, int lev, int levtop, int adr);//写语句
extern void loop(int btablev, int lev, int levtop, int adr);//循环
extern int expression(int btablev, int lev, int levtop, int adr);//表达式
extern void condition(int btablev, int lev, int levtop, int adr);//条件
extern void caseelement(int btablev, int i, int lev, int levtop, int adr);//情况元素表
extern void actParaList(int btablev, int i, int lev, int levtop, int adr);//实际参数表
extern int term(int btablev, int lev, int levtop, int adr);//项
extern int factor(int btablev, int lev, int levtop, int adr);//因子
extern int funcCall(int btablev, int lev, int levtop, int adr);//函数调用

extern int tabtest(int lev, char * name);//查重符号表
extern void tabtype(_SYMBOL symbol, int ternnum);//批量填充类型
extern void tabadr(int * adr, int num, int termnum);
extern void tabref(int atabtop, int termnum);
extern void tablink(int levtop, int termnum);
extern int tabfind(char * name, int levtop);//查符号表
extern void gen(int lev, int btablev, char * des, _OP opt, char * fir, char * sec);//生成四元式
extern void list_();//列出当前四元式
extern void constant(int lev, int btablev);//常量
