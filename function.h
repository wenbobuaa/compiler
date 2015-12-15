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
extern void subPro(int lev, int levtop, int adr);//�ֳ���
extern void consDef(int lev, int levtop);//��������
extern void constAnaly(int lev, int levtop);//��������
extern void varDef(int lev, int levtop, int * adr);//��������
extern void proHead(int lev, int levtop);//����ͷ��
extern void funcHead(int lev, int levtop);//����ͷ��
extern void formParaList(int lev, int levtop);//��ʽ������
extern void Type(int lev, int levtop, int * adr);//����
extern _SYMBOL baseType(int lev, int levtop);//��������
extern void formParaSeg(int lev, int levtop, int * adr);//��ʽ������
extern void comState(int btablev, int lev, int levtop, int adr);//�������
extern void state(int btablev, int lev, int levtop, int adr);//���
extern void assignment(int btablev, int i, int lev, int levtop, int adr);//��ֵ���
extern void conditionState(int btablev, int lev, int levtop, int adr);//�������
extern void caseState(int btablev, int lev, int levtop, int adr);//������
extern void proCall(int btablev, int i, int lev, int levtop, int adr);//���̵���
extern void readState(int btablev, int lev, int levtop, int adr);//�����
extern void writeState(int btablev, int lev, int levtop, int adr);//д���
extern void loop(int btablev, int lev, int levtop, int adr);//ѭ��
extern int expression(int btablev, int lev, int levtop, int adr);//���ʽ
extern void condition(int btablev, int lev, int levtop, int adr);//����
extern void caseelement(int btablev, int i, int lev, int levtop, int adr);//���Ԫ�ر�
extern void actParaList(int btablev, int i, int lev, int levtop, int adr);//ʵ�ʲ�����
extern int term(int btablev, int lev, int levtop, int adr);//��
extern int factor(int btablev, int lev, int levtop, int adr);//����
extern int funcCall(int btablev, int lev, int levtop, int adr);//��������

extern int tabtest(int lev, char * name);//���ط��ű�
extern void tabtype(_SYMBOL symbol, int ternnum);//�����������
extern void tabadr(int * adr, int num, int termnum);
extern void tabref(int atabtop, int termnum);
extern void tablink(int levtop, int termnum);
extern int tabfind(char * name, int levtop);//����ű�
extern void gen(int lev, int btablev, char * des, _OP opt, char * fir, char * sec);//������Ԫʽ
extern void list_();//�г���ǰ��Ԫʽ
extern void constant(int lev, int btablev);//����
