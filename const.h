#ifndef norw
#define norw	21	//保留字个数
#endif // norw

#ifndef txmax
#define txmax	100	//符号表的长度
#endif // txmax

#ifndef nmax
#define nmax	65535	//INTEGER的最大值
#endif // nmax

#ifndef al
#define al	18	//标识符的最大长度
#endif // al

#ifndef lmax
#define lmax	81  //行缓冲区的最大长度
#endif // lmax

#ifndef strmax
#define strmax	100	//字符串最大长度
#endif // strmax

#ifndef lsym
#define lsym 44 //symbol的个数
#endif

#ifndef SYMBOL
#define SYMBOL
    typedef enum SYMBOL_ { IDSY, ARRAYSY, BEGINSY, CASESY, CHARACTER, CONSTSY, DOSY, DOWNTO,
                    ELSESY, ENDSY, FORSY, FUNCSY, IFSY, INTEGER, OFSY, PROCSY, READSY, THENSY, TOSY,
                    VARSY, WRITESY, INTSY, CHARSY, STRSY, PLUSSY, MINUSSY, STARSY,DIVISY, LPASY, RPASY,
                    COLOSY, COMMASY, SEMISY, PERISY, BECOMESY, EQUSY, LESSSY, GREATSY,  LBRACSY, RBRACSY ,
                    UNEQUSY, LEQSY, GEQSY, nul} _SYMBOL;//单词类型助记符号
#endif // SYMBOL

#ifndef OBJ
#define OBJ
	typedef enum OBJ_ {CONST, VAR, FUNCTION, PROCEDURE, nulOBJ} _OBJ;
#endif

#ifndef BOOL
#define BOOL
	typedef enum BOOL_ {TRUE, FALSE, nulBOOL} _BOOL;
#endif

#ifndef TAB
#define TAB
	typedef struct TAB_ {//符号表
		char name[al];//标识符的名字
		_OBJ obj;//标识符的种类
		_SYMBOL typ;//标识符的类型
		int ref;//引用信息
		int lev;//层数
		_BOOL normal;//参数类型
		int adr;//值
		int link;//同一个分程序中上一个记录
	}_TAB;
#endif

#ifndef ATAB
#define ATAB
	typedef struct ATAB_{//数组
		_SYMBOL typ;//数组类型
		int high;//数组界限
		//int elsize;//数组元素大小
		//int size;//数组大小
	}_ATAB;
#endif

#ifndef BTAB
#define BTAB
	typedef struct BTAB_{//分程序
	    char name[al];
		int last;//分程序的最后一个标识符在tab中的位置
		int lastpar;//分程序的最后一个参数在tab中的位置
		int psize;//参数所占的存储单元数量
		int vsize;//局部变量所占的存储单元的数量
		int adr;//函数的运行地址基址
		int code;//生成指令的位置
	} _BTAB;
#endif

#ifndef OP
#define OP
	typedef enum OP_{//运算符
		nulOP, PLUS, MINUS, STAR, DIVI, EQU, UNE, GTH,
		LTH, GEQ, LEQ, LOD, CALLP, CALLF, STO, LAB, LI, ARRV,
		JMP, REDI, REDC, WRII, WRIC, WRIS, TRAV, TRAR, RETP, RETF, ARRA
	}_OP;
#endif

#ifndef CODE
#define CODE
	typedef struct CODE_ {//四元式
		char des[al];
		char fir[strmax];
		_OP opt;
		char sec[al];
		int lev;
        int ref;
	} _CODE;
#endif // CODE

#ifndef VARTAG
#define VARTAG
    typedef struct VARTAG_ {
        char name[al];
        int reg;
        int adr;
    } _VARTAG;
#endif // VARTAG
