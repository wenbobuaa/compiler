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

extern void grammar();//�﷨��������
extern void procedure();//����
extern void subPro();//�ֳ���
extern void consDef();//��������
extern void constAnaly();//��������
extern void varDef();//��������
extern void proHead();//����ͷ��
extern void funcHead();//����ͷ��
extern void formParaList();//��ʽ������
extern void Type();//����
extern _SYMBOL baseType();//��������
extern void formParaSeg();//��ʽ������
extern void comState();//�������
extern void state();//���
extern void assignment();//��ֵ���
extern void conditionState();//�������
extern void caseState();//������
extern void proCall();//���̵���
extern void readState();//�����
extern void writeState();//д���
extern void loop();//ѭ��
extern void expression();//���ʽ
extern void condition();//����
extern void caseelement();//���Ԫ�ر�
extern void actParaList();//ʵ�ʲ�����
extern void term();//��
extern void factor();//����
extern void funcCall();//��������

extern int tabtest(int lev, char * name);//���ط��ű�
extern void tabtype(_SYMBOL symbol, int ternnum);//�����������
extern void tabadr(int adrtop, int num, int termnum);
extern void tabref(int atabtop, int termnum);
extern void tablink(int levtop, int termnum);
extern int tabfind(char * name);//����ű�
extern void gen(char * des, _OP opt, char * fir, char * sec);//������Ԫʽ
extern void list();//�г���ǰ��Ԫʽ
extern void constant();//����