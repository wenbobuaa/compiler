#include <stdio.h>
#include "const.h"
#define DEBUG

extern SYMBOL symbol;//��ǰ��ȡ�ĵ��ʵ�����
extern char ch;//���ڴ�����ַ�
extern char token[al];//���浱ǰ��һ����ʶ��
extern int num;//����
extern char cha;//�ַ�
extern char str[strmax];//�ַ���
extern char line[81];//�л�����
extern int ll;//�к�
extern int cc;//�л�����ָ��
extern int kk;//��ʶ��ջָ��
extern int kkk;//�ַ���ջָ��
extern char * reserverTable[norw];//�����ֱ�
extern FILE * In;
extern FILE * Out;

extern int symNeed[lsym];//����Ҫ������ͱ�

extern _TAB[txmax] tab;//���ű�
extern _ATAB[40] atab;//������Ϣ������
extern _BTAB[40] btab;//�ֳ����
extern int[40] display;//�ֳ���������
extern int tabtop;//���ű�ջ��ָ��
extern int atabtop;//������Ϣ������ջ��ָ��
extern int btabtop;//�ֳ����ջ��ָ��
extern int termnum;//δ����ı���
extern _TAB tabnow;//��ǰһ�����ű���
extern _ATAB atabnow;//��ǰһ���������
extern _BTAB btabnow;//��ǰһ���ֳ������
//extern int lev;//��ǰ���� 
extern int adrtop;//��ǰ��ַ
//extern int opttop;//��ǰָ��λ��
extern _CODE[100] ctab;//��Ԫʽ�� 
extern int ctabtop;//��ǰָ��λ��
extern _CODE ctabnow;//��ǰָ������
extern int Tnum;//�м�������
extern int Label;//��־���