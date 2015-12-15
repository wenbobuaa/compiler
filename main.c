#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

#define norw	21	//保留字个数
#define txmax	100	//符号表的长度
#define nmax	14	//数字的最大长度
#define al	18	//标识符的最大长度
#define lmax	81  //行缓冲区的最大长度
#define strmax	100	//字符串最大长度



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
