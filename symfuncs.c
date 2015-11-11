#include "compiler.h"

void getchar(){
	ch = line[cc];
	cc += 1;
}

void clearToken(){
	Token[kk] = '\0';
	kk = 0;
}

void catToken(){
	Token[kk] = ch;
	kk += 1;
}

void retract(){
	cc -= 1;
}

int isSpace(){
	if( ch == ' ' ){
		return 1;
	}else{
		return 0;
	}
}

int isNewline(){
	if( ch == '\n' ){
		return 1;
	}else{
		return 0;
	}
}

int isTab(){
	if( ch == '\t' ){
		return 1;
	}else{
		return 0;
	}
}

int isLetter(){
	if( ch >= 'a' && ch <= 'Z' ){
		return 1;
	}else{
		return 0;
	}
}

int isChar(){
	if( ch == ' ' || ch == '!' ){
		return 1;
	}else if( ch >= 35 && ch <= 126 ){
		return 1;
	}else{
		return 0;
	}
}

int isDigit(){
	if( ch >= '0' && ch <= '9' ){
		return 1;
	}else{
		return 0;
	}
}

int isColon(){
	if( ch == ',' ){
		return 1;
	}else{
		return 0;
	}
}

int isComma(){
	if( ch == ':' ){
		return 1;
	}else{
		return 0;
	}
}

int isSemi(){
	if( ch == ';' ){
		return 1;
	}else{
		return 0;
	}
}

int isQuot(){
	if( ch == '"' ){
		return 1;
	}else{
		return 0;
	}
}
int isEqu(){
	if( ch == '=' ){
		return 1;
	}else{
		return 0;
	}
}

int isPlus(){
	if( ch == '+' ){
		return 1;
	}else{
		return 0;
	}
}

int isMinus(){
	if( ch == '-' ){
		return 1;
	}else{
		return 0;
	} 
}

int isDivi(){
	if( ch == '/' ){
		return 1;
	}else{
		return 0;
	}
}

int isStar(){
	if( ch == '*' ){
		return 1;
	}else{ 
		return 0;
	}
}

int isLpar(){
	if( ch == '(' ){
		return 1;
	}else{
		return 0;
	}
}

int isRpar(){
	if( ch == ')' ){
		return 1;
	}else{
		return 0;
	}
}

int reserver(){

}

void error(){

}

int transNum(){
	int result = 0;
	int i = 0;

	/*if(Token[i] == '0'){
		error();
	}*/

	for(i = 0; Token[i] != '\0'; i++){
		result = result*10 + Token[i];
	}
	return result;
}
