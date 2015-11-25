#include <stdio.h>
#include <stdlib.h>

#define norw	21	//保留字个数
#define txmax	100	//符号表的长度
#define nmax	14	//数字的最大长度
#define al	18	//标识符的最大长度
#define lmax	81  //行缓冲区的最大长度
#define strmax	100	//字符串最大长度
#define lsym 44	//symbol的个数


typedef enum SYMBOL_ { IDSY, ARRAYSY, BEGINSY, CASESY, CHARACTER, CONSTSY, DOSY, DOWNTO, ELSESY, ENDSY, FORSY, FUNCSY, IFSY, INTEGER, OFSY, PROCSY, READSY, THENSY, TOSY, VARSY, WRITESY,
			  INTSY, CHARSY, STRSY, PLUSSY, MINUSSY, STARSY,DIVISY, LPASY, RPASY, COLOSY, COMMASY, SEMISY, PERISY, BECOMESY, EQUSY, LESSSY, GREATSY,  LBRACSY, RBRACSY , UNEQUSY, LEQSY, GEQSY, nul} SYMBOL;//单词类型助记符号
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
void consDef();//常量定义
void constAnaly();//常量分析
void varDef();//变量定义
void proHead();//过程头部
void funcHead();//函数头部
void formParaList();//形式参数表
void Type();//类型
void baseType();//基本类型
void formParaSeg();//形式参数段
void comState();//复合语句
void state();//语句
void assignment();//赋值语句
void conditionState();//条件语句
void caseState();//情况语句
void proCall();//过程调用
void readState();//读语句
void writeState();//写语句
void loop();//循环
void expression();//表达式
void condition();//条件
void caseelement();//情况元素表
void actParaList();//实际参数表
void term();//项
void factor();//因子
void funcCall();//函数调用