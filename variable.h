#include <stdio.h>
#include "const.h"
//#define DEBUG

extern _SYMBOL symbol;//��ǰ��ȡ�ĵ��ʵ�����
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
extern FILE * MOUT;
extern int errornum;

extern int symNeed[lsym];//����Ҫ������ͱ�

extern _TAB tab[txmax];//���ű�
extern _ATAB atab[40];//������Ϣ������
extern _BTAB btab[40];//�ֳ����
extern int display [40];//�ֳ���������
extern int tabtop;//���ű�ջ��ָ��
extern int atabtop;//������Ϣ������ջ��ָ��
extern int btabtop;//�ֳ����ջ��ָ��
extern int termnum;//δ����ı���
extern _TAB tabnow;//��ǰһ�����ű���
extern _ATAB atabnow;//��ǰһ���������
extern _BTAB btabnow;//��ǰһ���ֳ������
//extern int publev;//��ǰ����
//extern int adrtop;//��ǰ��ַ
//extern int opttop;//��ǰָ��λ��
extern _CODE ctab[10000];//��Ԫʽ��
extern int ctabtop;//��ǰָ��λ��
extern _CODE ctabnow;//��ǰָ������
extern int Tnum;//�м�������
extern int Label;//��־���

extern int regtab[32];//����Ĵ�����ʹ����Ϣ
extern int regtabbuf[32];//regtab�ı���
extern int regnum[32];//reg��ʹ�ô���
extern _VARTAG vartab[100];
extern int vartabtop;
extern int nowctabadr;
extern int ref;
