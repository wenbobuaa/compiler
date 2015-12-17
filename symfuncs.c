#include "function.h"
#include "variable.h"

void getChar(){
	if(line[cc] == '\0'){
		if(getLine()){
			cc = 0;
			ch = line[cc];
			cc += 1;
		}else{
			ch = '\0';
		}
	}else{
		ch = line[cc];
		cc += 1;
	}
}

int getLine(){
	if(fgets(line, lmax, In) != NULL){
		ll++;
		return 1;
	}else{
		return 0;
	}
}

void clearToken(){
	token[kk] = '\0';
	kk = 0;
}

void clearString(){
	str[kkk] = '\0';
	kkk = 0;
}


int isEnd(){
	if(ch == '\0'){
		return 1;
	}else{
		return 0;
	}
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
	if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ){
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
	if( ch == ':' ){
		return 1;
	}else{
		return 0;
	}
}

int isComma(){
	if( ch == ',' ){
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
int isPeri(){
    if(ch == '.'){
        return 1;
    }else{
        return 0;
    }
}

int isSquot(){
	if( ch == '\'' ){
		return 1;
	}else{
		return 0;
	}
}

int isDquot(){
	if( ch == '"' ){
		return 1;
	}else{
		return 0;
	}
}

int isLbrac(){
	if(ch == '['){
		return 1;
	}else{
		return 0;
	}
}

int isRbrac(){
	if(ch == ']'){
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

int isLess(){
	if( ch == '<' ){
		return 1;
	}else{
		return 0;
	}
}

int isGreat(){
	if( ch == '>' ){
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

void catToken(){
    int temp = 0;
    temp = 'A' - 'a';
	if(kk == al - 1){
		clearToken();
	}else{
        if(ch >= 'A' && ch <= 'Z'){
            ch = ch - temp;
        }
		token[kk] = ch;
		kk += 1;
	}
}

void catString(){
	if(kkk == strmax - 1){
		clearString();
	}else{
		str[kkk] = ch;
		kkk += 1;
	}
}

void retract(){
	cc -= 1;
}

SYMBOL reserver(){
	int star = 1;
	int	end = norw - 1;
	int mid;
	while( star <= end ){
		mid = (star + end) / 2;
		if(strcmp(token, reserverTable[mid]) < 0){
			end = mid - 1;
		}else if(strcmp(token, reserverTable[mid]) > 0){
			star = mid + 1;
		}else{
			return mid;
		}
	}
	return 0;
}

int transNum(){
	int result = 0;
	int i = 0;

	/*if(Token[i] == '0'){
		error();
	}*/

	for(i = 0; token[i] != '\0'; i++){
		result = result*10 + token[i] - '0';
	}
	return result;
}

void error(int sw){
	int i = 0;
	errornum++;
	printf("ERROE!\n");
	printf("%4d: ", ll);
	printf("%s\n", line);
	printf("******");
	while(i++ < cc - 1){
		printf("*");
	}
	printf("^\n\n");
	switch (sw){
		case 0 : printf("Needs a letter or a digit.[a-zA-Z0-9]\n");break;
		case 1 : printf("Needs a single quote.\n");break;
		case 2 : printf("Needs a double quote.\n");break;
		case 3 : printf("Unknown character.\n");break;
		default : ;
	}
	symbol = nul;
}

void initReserver(){
	reserverTable[0] = " ";
	reserverTable[1] = "array";
	reserverTable[2] = "begin";
	reserverTable[3] = "case";
	reserverTable[4] = "char";
	reserverTable[5] = "const";
	reserverTable[6] = "do";
	reserverTable[7] = "downto";
	reserverTable[8] = "else";
	reserverTable[9] = "end";
	reserverTable[10] = "for";
	reserverTable[11] = "function";
	reserverTable[12] = "if";
	reserverTable[13] = "integer";
	reserverTable[14] = "of";
	reserverTable[15] = "procedure";
	reserverTable[16] = "read";
	reserverTable[17] = "then";
	reserverTable[18] = "to";
	reserverTable[19] = "var";
	reserverTable[20] = "write";
}
