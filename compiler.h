#define norw	13	//保留字个数
#define txmax	100	//符号表的长度
#define nmax	14	//数字的最大长度
#define al		10	//标识符的最大长度

enum symbol { nul, BEGINSY, ENDSY, IFSY, THENSY, ELSESY, 
	        IDSY, CONSTSY, VARSY, PROCSY, READSY, WRITESY,
			DOSY, WHILESY, CALLSY, INTSY, REALSY, PLUSSY, 
			MINUSSY, STARSY, DIVISY, LPASY, RPASY,COLOSY,
			COMMASY, SEMISY, PERISY, BECOMESY, ODDSY };
enum object { CONSTSY, VARSY, PROCSY };
enum fct { };

char ch;
char[18] token;
int num;
char[81] line;
int cc = 0;
int kk = 0;

void getchar();
void clearToken();
int isSpace();
int isNewline();
int isTab();
int isLetter();
int isDigit();
int isColon();
int isComma();
int isSemi();
int isEqu();
int isPlus();
int isMinus();
int isStar();
int isDivi();
int isLpar();
int isRpar();
void catToken();
void retract();
int reserver();
int transNum();
void erro();
