#include <stdlib.h>
#include "const.h"

extern void getChar();//��һ���ַ�
extern int getLine();//���µ�һ��
extern void clearToken();//��ǰ�ַ�����ȡ���
extern void clearString();//�ַ����������
extern int isEnd();
extern int isSpace();//�ո�
extern int isNewline();//����
extern int isTab();//tab
extern int isLetter();//��ĸ
extern int isChar();//�ַ�
extern int isDigit();//����
extern int isColon();//ð��
extern int isComma();//����
extern int isSemi();//�ֺ�
extern int isPeri();//���
extern int isSquot();//������
extern int isDquot();//˫����
extern int isLbrac();//��������
extern int isRbrac();//��������
extern int isEqu();//�Ⱥ�
extern int isLess();//С�ں�
extern int isGreat();//���ں�
extern int isPlus();//+
extern int isMinus();//-
extern int isStar();//*
extern int isDivi();///
extern int isLpar();//(
extern int isRpar();//)
extern void catToken();//���һ���ַ�
extern void catString();//���ַ������һ���ַ�
extern void retract();//����һ���ַ�
extern SYMBOL reserver();//�鱣����
extern int transNum();//ת��������
extern void erro(int sw);//����
extern void initReserver();//��ʼ�������ֱ�
extern void getsym();//�ʷ���������
