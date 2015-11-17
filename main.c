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
	if(Out != NULL){
		fclose(Out);
	}
}

int main(){
	In = fopen("_test.txt", "r");
	Out = fopen("_symout.txt", "w");
	if(In == NULL){
		printf("Cannot find file _test.txt.\n");
		return 1;
	}
	if(Out == NULL){
		printf("Cannot open file _symout.txt");
		return 1;
	}
	if(fgets(line, lmax, In) == NULL){
		printf("Empty file.");
		fileclose();
		return 1;
	}
	initReserver();
	getChar();
	getsym();
	while(symbol != nul){
		switch(symbol){
			case IDSY : fprintf(Out, "ID %s\n", token);break;
			case ARRAYSY : fprintf(Out, "ARRAY %s\n", token);break;
			case BEGINSY : fprintf(Out, "BEGIN %s\n", token);break;
			case CASESY : fprintf(Out, "CASE %s\n", token);break;
			case CHARACTER : fprintf(Out, "CHAR %s\n", token);break;
			case CONSTSY : fprintf(Out, "CONST %s\n", token);break;
			case DOSY : fprintf(Out, "DO %s\n", token);break;
			case DOWNTO : fprintf(Out, "DOWNTO %s\n", token);break;
			case ELSESY : fprintf(Out, "ELSESY %s\n", token);break;
			case ENDSY : fprintf(Out, "END %s\n", token);break;
			case FORSY : fprintf(Out, "FOR %s\n", token);break;
			case FUNCSY : fprintf(Out, "FUNCTION %s\n", token);break;
			case IFSY : fprintf(Out, "IF %s\n", token);break;
			case INTEGER : fprintf(Out, "INTEGER %s\n", token);break;
			case OFSY : fprintf(Out, "OF %s\n", token);break;
			case PROCSY : fprintf(Out, "PROCEDRUE %s\n", token);break;
			case READSY : fprintf(Out, "READ %s\n", token);break;
			case THENSY : fprintf(Out, "THEN %s\n", token);break;
			case TOSY : fprintf(Out, "TO %s\n", token);break;
			case VARSY : fprintf(Out, "VAR %s\n", token);break;
			case WRITESY : fprintf(Out, "WRITE %s\n", token);break;

			case INTSY : fprintf(Out, "INT %d\n", num);break;
			case CHARSY : fprintf(Out, "CHAR %c\n", cha);break;
			case STRSY : fprintf(Out, "STRING %s\n", str);break;
			case PLUSSY : fprintf(Out, "PLUS %c\n", ch);break;
			case MINUSSY : fprintf(Out, "MINUS %c\n", ch);break;
			case STARSY : fprintf(Out, "STAR %c\n", ch);break;
			case DIVISY : fprintf(Out, "DIVI %c\n", ch);break;
			case LPASY : fprintf(Out, "LPAR %c\n", ch);break;
			case RPASY : fprintf(Out, "RPAR %c\n", ch);break;
			case COLOSY : fprintf(Out, "COLON %s\n", token);break;
			case COMMASY : fprintf(Out, "COMMA %c\n", ch);break;
			case SEMISY : fprintf(Out, "SEMICOLON %c\n", ch);break;
			case PERISY : fprintf(Out, "PERIOD %c\n", ch);break;
			case BECOMESY : fprintf(Out, "BECOME %s\n", token);break;
			case EQUSY : fprintf(Out, "EQUAL %c\n", ch);break;
			case LESSSY : fprintf(Out, "LESS %s\n", token);break;
			case GREATSY : fprintf(Out, "GREAT %s\n", token);break;
			case LBRACSY : fprintf(Out, "LBRACKET %c\n", ch);break;
			case RBRACSY : fprintf(Out, "RBRACKET %c\n", ch);break;
			case UNEQUSY : fprintf(Out, "UNEQUAL %s\n", token);break;
			case LEQSY : fprintf(Out, "LESSOREQU %s\n", token);break;
			case GEQSY : fprintf(Out, "GREATEROREQU %s\n", token);break;
			default : printf("\n");
		}
		getChar();
		getsym();
	}
	fileclose();
	return 0;
}
