#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

#define norw	21	//�����ָ���
#define txmax	100	//���ű�ĳ���
#define nmax	14	//���ֵ���󳤶�
#define al	18	//��ʶ������󳤶�
#define lmax	81  //�л���������󳤶�
#define strmax	100	//�ַ�����󳤶�



void fileclose(){
	if( In != NULL){
		fclose(In);
	}
	if(MOUT != NULL){
        fclose(MOUT);
	}
}

int main(){
	int i = 0;
	//char temp[al];
	In = fopen("13061151_test.txt", "r");
	MOUT = fopen("code.asm", "w");
	if(In == NULL){
		printf("Cannot find file _test.txt.\n");
		return 1;
	}
	if(MOUT == NULL){
		printf("Cannot find file code.asm.\n");
		return 1;
	}
	if(fgets(line, lmax, In) == NULL){
		printf("Empty file.");
		fileclose();
		return 1;
	}
	initReserver();
	for(i = 0; i < lsym; i++){
		symNeed[i] = 0;
        //itoa(-1*i, temp, al);
       //printf("%s\n", temp);
	}
	grammar();
	printf("grammar finished.\n");

    fprintf(MOUT, ".test\n");
	trans();
	fileclose();
	return 0;
}
