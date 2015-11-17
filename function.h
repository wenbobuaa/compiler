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
